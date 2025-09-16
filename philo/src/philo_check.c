/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/16 12:12:32 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		control_aux(tab, i);
		sec_control_aux(tab, i);
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
			pthread_mutex_lock(philo->tab->death);
			philo->tab->death_flag = 1;
			pthread_mutex_unlock(philo->tab->death);
			print_mutex_death_use(philo, "died");
		}
		else
			if (routine_aux(philo) == EXIT_FAILURE)
				break ;
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
