/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/08/29 16:26:51 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	current_time;
	long long		milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000LL)
		+ (current_time.tv_usec / 1000);
	return (milliseconds);
}

void	set_start_time(t_table *tab)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	tab->starttime = (start_time.tv_sec * 1000LL)
		+ (start_time.tv_usec / 1000);
}

void	philo_routine(t_table *tab)
{
	usleep(tab->death_time * 1000);
	printf("%lld 0 died.\n", tab->death_time);
}
