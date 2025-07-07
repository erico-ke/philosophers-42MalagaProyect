/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:07 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_mutex_init(t_table *tab)
{
	if (pthread_mutex_init(tab->writer, NULL) == -1)
			return (prnt_err("Mutex init failed"));
	return (EXIT_SUCCESS);
}

void	print_mutex_use(t_table *tab, char *msg)
{
	pthread_mutex_lock(tab->writer);
	if (tab->death_flag == 0)
		printf("%lld %d %s\n", get_time(), tab->philosophers[0]->id, msg);
	pthread_mutex_unlock(tab->writer);	
}

void	fork_mutex_use(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	if (philo->tab->death_flag == 0)
	{
		print_mutex_use(philo->tab, "has taken a fork");
		print_mutex_use(philo->tab, "has taken a fork");
		print_mutex_use(philo->tab, "is eating");
		usleep(philo->tab->eat_time * 1000);
		philo->is_eating = 1;
		philo->last_time_eated = get_time();
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}