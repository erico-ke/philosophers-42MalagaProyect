/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/01 11:44:43 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *tab)
{
	usleep(tab->death_time * 1000);
	printf("at %lld miliseconds philo 0 died.", tab->death_time);
}

		//inicializar mutex, luego los threads, los threads necesitan la rutina
		//de los philos, crearla.
		//checkear que no se bloqueen, hacer la logica de los mutex correctamente.

int	philo_pthread_init(t_table *tab, int i)
{
	tab->philosophers[i] = malloc(sizeof(t_philo));
	if (!tab->philosophers[i])
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) != 0)
		return (EXIT_FAILURE);
	i++;
	while (i < tab->philo_amount)
	{
		tab->philosophers[i] = malloc(sizeof(t_philo));
		if (!tab->philosophers[i])
			return (EXIT_FAILURE);
		if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) != 0)
			return (EXIT_FAILURE);
		tab->philosophers[i]->r_fork = tab->philosophers[i - 1]->l_fork;
		i++;	
	}
	tab->philosophers[0]->r_fork = tab->philosophers[i - 1]->l_fork;
	return (EXIT_SUCCESS);
}
