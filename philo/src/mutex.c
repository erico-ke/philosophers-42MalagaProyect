/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 15:09:34 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_mutex_init(t_table *tab)
{
	if (pthread_mutex_init(tab->writer, NULL) == -1)
		return (prnt_err("Mutex init failed"));
	if (pthread_mutex_init(tab->death, NULL) == -1)
		return (prnt_err("Mutex init failed"));
	return (EXIT_SUCCESS);
}

void	print_mutex_use(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->tab->death);
	if (philo->tab->death_flag == 0)
	{
		pthread_mutex_lock(philo->tab->writer);
		printf("%lld %d %s\n", get_time()
			- philo->tab->starttime, philo->id, msg);
		pthread_mutex_unlock(philo->tab->writer);
	}
	pthread_mutex_unlock(philo->tab->death);
}

void	fork_mutex_use(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_mutex_use(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_mutex_use(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_mutex_use(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_mutex_use(philo, "has taken a fork");
	}
	print_mutex_use(philo, "is eating");
	usleep(philo->tab->eat_time * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	print_mutex_death_use(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->tab->writer);
	printf("%lld %d %s\n", get_time() - philo->tab->starttime, philo->id, msg);
	pthread_mutex_unlock(philo->tab->writer);
}
