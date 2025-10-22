/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:05:12 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 16:06:42 by erico-ke         ###   ########.fr       */
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
	tab->philosophers[i]->meal_lock = malloc(sizeof(pthread_mutex_t));
	if (!tab->philosophers[i]->meal_lock)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->meal_lock, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_philosopher_death(t_philo *philo)
{
	long long	time_since_meal;

	pthread_mutex_lock(philo->meal_lock);
	time_since_meal = get_time() - philo->last_time_eated;
	pthread_mutex_unlock(philo->meal_lock);
	if (time_since_meal >= philo->tab->death_time)
	{
		pthread_mutex_lock(philo->tab->death);
		if (philo->tab->death_flag == 0)
		{
			philo->tab->death_flag = 1;
			pthread_mutex_unlock(philo->tab->death);
			print_mutex_death_use(philo, "died");
			return (1);
		}
		pthread_mutex_unlock(philo->tab->death);
	}
	return (0);
}

int	check_all_full(t_table *tab)
{
	int	i;
	int	all_full;

	if (tab->nbr_eat == -1)
		return (0);
	i = 0;
	all_full = 1;
	while (i < tab->philo_amount)
	{
		pthread_mutex_lock(tab->philosophers[i]->meal_lock);
		if (tab->philosophers[i]->times_eat < tab->nbr_eat)
			all_full = 0;
		pthread_mutex_unlock(tab->philosophers[i]->meal_lock);
		i++;
	}
	if (all_full)
	{
		pthread_mutex_lock(tab->death);
		tab->death_flag = 1;
		pthread_mutex_unlock(tab->death);
		return (1);
	}
	return (0);
}

int	routine_aux(t_philo *philo)
{
	int	should_stop;

	fork_mutex_use(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->times_eat++;
	should_stop = (philo->times_eat == philo->tab->nbr_eat);
	pthread_mutex_unlock(philo->meal_lock);
	if (should_stop)
		return (EXIT_FAILURE);
	print_mutex_use(philo, "is sleeping");
	usleep(philo->tab->sleep_time * 1000);
	print_mutex_use(philo, "is thinking");
	return (EXIT_SUCCESS);
}
