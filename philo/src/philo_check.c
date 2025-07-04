/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/04 16:59:47 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *tab)
{
	usleep(tab->death_time * 1000);
	printf("at %lld miliseconds philo 0 died.", tab->death_time);
}

int	philo_pthread_init(t_table *tab, int i)
{
	tab->philosophers = malloc(sizeof(t_philo *) * tab->philo_amount);
	if (!tab->philosophers)
		return (EXIT_FAILURE);
	while (++i < tab->philo_amount)
	{
		tab->philosophers[i] = malloc(sizeof(t_philo));
		if (!tab->philosophers[i])
			return (EXIT_FAILURE);
		tab->philosophers[i]->l_fork = malloc(sizeof(pthread_mutex_t));
		if (!tab->philosophers[i]->l_fork)
			return (EXIT_FAILURE);
		if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) == -1)
			return (EXIT_FAILURE);
		tab->philosophers[i]->id = i;
		tab->philosophers[i]->is_eating = 0;
		tab->philosophers[i]->last_time_eated = 0;
		tab->philosophers[i]->is_sleeping = 0;
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
	while (1)
	{
		i = -1;
		while (++i < tab->philo_amount)
		{
			printf("%d", tab->philosophers[i]->is_alive);
			if (tab->philosophers[i]->is_alive == 1)
			{
				tab->death_flag = 1;
				break ;
			}
		}
		if (tab->death_flag == 1)
			break ;
	}
	i = -1;
	while (++i < tab->philo_amount)
		tab->philosophers[i]->is_alive = 1;
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->is_alive != 1)
	{
		
	}
	return (NULL);
}

void	philos_pthread_create(t_table *tab, int i)
{
	pthread_create(&tab->thread, NULL, control, tab);
	while (++i < tab->philo_amount)
	{
		tab->philosophers[i]->tab = tab;
		pthread_create(&tab->philosophers[i]->thread, NULL, routine, tab->philosophers[i]);
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

