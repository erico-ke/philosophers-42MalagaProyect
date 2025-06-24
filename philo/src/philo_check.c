/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/24 18:03:15 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *tab)
{
	usleep(tab->death_time * 1000);
	printf("at %lld miliseconds philo 0 died.", tab->death_time);
}
