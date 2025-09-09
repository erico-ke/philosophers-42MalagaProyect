/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/09 18:26:18 by erico-ke         ###   ########.fr       */
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
	pthread_mutex_lock(philo->tab->writer);
	pthread_mutex_lock(philo->tab->death);
	if (philo->tab->death_flag != 1)
		printf("%lld %d %s\n", get_time()
			- philo->tab->starttime, philo->id, msg);
	pthread_mutex_unlock(philo->tab->writer);
	pthread_mutex_unlock(philo->tab->death);

}

void	fork_mutex_use(t_philo *philo)
{
	pthread_mutex_lock(philo->tab->death);
	if (philo->tab->death_flag == 0)
	{
		pthread_mutex_unlock(philo->tab->death);
		if (philo->id == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_mutex_use(philo, "has taken the left fork");
			pthread_mutex_lock(philo->r_fork);
			print_mutex_use(philo, "has taken the right fork");
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			print_mutex_use(philo, "has taken the right fork");
			pthread_mutex_lock(philo->l_fork);
			print_mutex_use(philo, "has taken the left fork");
		}
		print_mutex_use(philo, "is eating");
		philo->is_eating = 1;
		usleep(philo->tab->eat_time * 1000);
		philo->last_time_eated = get_time();
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(philo->tab->death);
	}
	pthread_mutex_unlock(philo->tab->death);
}

void	print_mutex_death_use(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->tab->writer);
	printf("%lld %d %s\n", get_time() - philo->tab->starttime, philo->id, msg);
	pthread_mutex_unlock(philo->tab->writer);
}
