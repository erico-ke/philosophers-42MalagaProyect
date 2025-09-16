/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:05:12 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/16 12:12:36 by erico-ke         ###   ########.fr       */
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

void	control_aux(t_table *tab, int i)
{
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
}

void	sec_control_aux(t_table *tab, int i)
{
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
}

int	routine_aux(t_philo *philo)
{
	fork_mutex_use(philo);
	philo->last_time_eated = get_time();
	pthread_mutex_lock(philo->t_eated);
	philo->times_eat++;
	if (philo->times_eat == philo->tab->nbr_eat)
	{
		pthread_mutex_unlock(philo->t_eated);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(philo->t_eated);
	print_mutex_use(philo, "is sleeping");
	usleep(philo->tab->sleep_time * 1000);
	print_mutex_use(philo, "is thinking");
	return (EXIT_SUCCESS);
}
