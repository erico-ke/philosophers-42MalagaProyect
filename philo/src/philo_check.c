/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 15:11:08 by erico-ke         ###   ########.fr       */
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
		tab->philosophers[i]->id = i + 1;
		tab->philosophers[i]->is_eating = 0;
		tab->philosophers[i]->last_time_eated = 0;
		tab->philosophers[i]->times_eat = 0;
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
	while (1)
	{
		if (check_all_full(tab))
			return (NULL);
		i = 0;
		while (i < tab->philo_amount)
		{
			if (check_philosopher_death(tab->philosophers[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->tab->death);
	dead = philo->tab->death_flag;
	pthread_mutex_unlock(philo->tab->death);
	return (dead);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_time_eated = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	while (!is_dead(philo))
	{
		if (routine_aux(philo) == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}

void	philos_pthread_create(t_table *tab, int i)
{
	tab->writer = malloc(sizeof(pthread_mutex_t));
	if (!tab->writer)
	{
		prnt_err("Failed to allocate memory for writer mutex");
		return ;
	}
	tab->death = malloc(sizeof(pthread_mutex_t));
	if (!tab->death)
	{
		prnt_err("Failed to allocate memory for death mutex");
		return ;
	}
	if (print_mutex_init(tab) == EXIT_FAILURE)
		return ;
	while (++i < tab->philo_amount)
	{
		tab->philosophers[i]->tab = tab;
		pthread_create(&tab->philosophers[i]->thread, NULL, routine,
			tab->philosophers[i]);
		usleep(100);
	}
	pthread_create(&tab->thread, NULL, control, tab);
}
