/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/12 03:59:11 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_init_aux(t_table *tab, int i)
{
	tab->philosophers[i] = malloc(sizeof(t_philo));
	if (!tab->philosophers[i])
		return (EXIT_FAILURE);
	tab->philosophers[i]->l_fork = malloc(sizeof(pthread_mutex_t));
	if (!tab->philosophers[i]->l_fork)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) == -1)
		return (EXIT_FAILURE);
	tab->philosophers[i]->alive = malloc(sizeof(pthread_mutex_t));
	if (!tab->philosophers[i]->alive)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->alive, NULL) == -1)
		return (EXIT_FAILURE);
	tab->philosophers[i]->t_eated = malloc(sizeof(pthread_mutex_t));
	if (!tab->philosophers[i]->t_eated)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->t_eated, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_pthread_init(t_table *tab, int i)
{
	tab->philosophers = malloc(sizeof(t_philo *) * tab->philo_amount);
	if (!tab->philosophers)
		return (EXIT_FAILURE);
	while (++i < tab->philo_amount)
	{
		if (pthread_init_aux(tab, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tab->philosophers[i]->id = i;
		tab->philosophers[i]->is_eating = 0;
		tab->philosophers[i]->last_time_eated = 0;
		tab->philosophers[i]->times_eat = 0;
		tab->philosophers[i]->is_alive = 0;
		if (i == tab->philo_amount - 1)
			tab->philosophers[i]->r_fork = tab->philosophers[0]->l_fork;
	}
	while (--i >= 0)
		if (i != tab->philo_amount - 1)
			tab->philosophers[i]->r_fork = tab->philosophers[i + 1]->l_fork;
	return (EXIT_SUCCESS);
}

/* La death flag deberia solo modificarse desde control, arreglar. sacarla de la 
rutina de philos no afecta el funcionamiento del programa. se puede prescindir del mutex.

Cuando se separa en partes control deja de funcionar correctamente el programa
revisar si es culpa de iteradores o de un cambio de logica necesario para particionar
la funcion. 

Posible solucion al problema de la cantidad de lineas por funcion es crear mini
funciones dedicadas al uso de los mutex, por ejemplo el de death_flag*/

static void	*control(void *arg)
{
	t_table	*tab;
	int		i;

	tab = (t_table *)arg;
	pthread_mutex_lock(tab->death);
	while (tab->death_flag != 1)
	{
		pthread_mutex_unlock(tab->death);
		i = -1;
		while (++i < tab->philo_amount)
		{
			pthread_mutex_lock(tab->death);
			tab->death_flag = 0;
			pthread_mutex_unlock(tab->death);
			pthread_mutex_lock(tab->philosophers[i]->t_eated);
			if (tab->philosophers[i]->times_eat == tab->nbr_eat)
			{
				pthread_mutex_unlock(tab->philosophers[i]->t_eated);
				pthread_mutex_lock(tab->death);
				tab->death_flag = 1;
				pthread_mutex_unlock(tab->death);
			}
			else
			{
				pthread_mutex_unlock(tab->philosophers[i]->t_eated);
				break ;
			}
		}
		i = -1;
		while (++i < tab->philo_amount)
		{
			pthread_mutex_lock(tab->philosophers[i]->alive);
			if (tab->philosophers[i]->is_alive == 1)
			{
				pthread_mutex_lock(tab->death);
				tab->death_flag = 1;
				pthread_mutex_unlock(tab->death);
			}
			pthread_mutex_unlock(tab->philosophers[i]->alive);
		}
		pthread_mutex_lock(tab->death);
	}
	pthread_mutex_unlock(tab->death);
	i = -1;
	while (++i < tab->philo_amount)
	{
		pthread_mutex_lock(tab->philosophers[i]->alive);
		tab->philosophers[i]->is_alive = 1;
		pthread_mutex_unlock(tab->philosophers[i]->alive);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_time_eated = get_time();
	pthread_mutex_lock(philo->alive);
	while (philo->is_alive != 1)
	{
		pthread_mutex_unlock(philo->alive);
		if (get_time() - philo->last_time_eated >= philo->tab->death_time)
		{
			pthread_mutex_lock(philo->alive);
			philo->is_alive = 1;
			pthread_mutex_unlock(philo->alive);
			/* pthread_mutex_lock(philo->tab->death);
			philo->tab->death_flag = 1;
			pthread_mutex_unlock(philo->tab->death); */
			print_mutex_death_use(philo, "died");
		}
		else
		{
			fork_mutex_use(philo);
			philo->last_time_eated = get_time();
			pthread_mutex_lock(philo->t_eated);
			philo->times_eat++;
			if (philo->times_eat == philo->tab->nbr_eat)
			{
				pthread_mutex_unlock(philo->t_eated);
				break ;
			}
			pthread_mutex_unlock(philo->t_eated);
			print_mutex_use(philo, "is sleeping");
			usleep(philo->tab->sleep_time * 1000);
			print_mutex_use(philo, "is thinking");
		}
		pthread_mutex_lock(philo->alive);
	}
	pthread_mutex_unlock(philo->alive);
	return (NULL);
}

void	philos_pthread_create(t_table *tab, int i)
{
	set_start_time(tab);
	tab->writer = malloc(sizeof(pthread_mutex_t));
	if (!tab->writer)
	{
		prnt_err("Failed to allocate memory for writer mutex");
		return ;
	}
	tab->death = malloc(sizeof(pthread_mutex_t));
	if (!tab->death)
	{
		prnt_err("Failed to allocate memory for writer mutex");
		return ;
	}
	if (print_mutex_init(tab) == EXIT_FAILURE)
		return ;
	pthread_create(&tab->thread, NULL, control, tab);
	while (++i < tab->philo_amount)
	{
		tab->philosophers[i]->tab = tab;
		pthread_create(&tab->philosophers[i]->thread, NULL, routine,
			tab->philosophers[i]);
		usleep(100);
	}
}

void	philos_pthread_join(t_table *tab)
{
	int	i;

	i = -1;
	while (++i < tab->philo_amount)
		pthread_join(tab->philosophers[i]->thread, NULL);
	pthread_join(tab->thread, NULL);
}
