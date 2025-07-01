/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:28:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/01 14:47:45 by erico-ke         ###   ########.fr       */
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
	tab->philosophers = malloc(sizeof(t_philo *));
	tab->philosophers[i] = malloc(sizeof(t_philo));
	if (!tab->philosophers[i])
		return (EXIT_FAILURE);
	if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) == -1)
		return (EXIT_FAILURE);
	while (++i < tab->philo_amount)
	{
		tab->philosophers[i] = malloc(sizeof(t_philo));
		if (!tab->philosophers[i])
			return (EXIT_FAILURE);
		if (pthread_mutex_init(tab->philosophers[i]->l_fork, NULL) == -1)
			return (EXIT_FAILURE);
		tab->philosophers[i]->r_fork = tab->philosophers[i - 1]->l_fork;
		i++;	
	}
	tab->philosophers[0]->r_fork = tab->philosophers[i - 1]->l_fork;
	return (EXIT_SUCCESS);
}

static void	*control(t_table *tab, int i)
{
	int	check;

	check = 0;
	while (1)
	{
		i = 0;
		while (tab->philosophers[i])
			if (tab->philosophers[i]->is_alive == 1)
				check = 1;
		if (check == 1)
			break ;
	}
	i = -1;
	while (tab->philosophers[++i])
		pthread_detach(tab->philosophers[i]->thread);
	return (NULL);
}

static void	*routine(t_table *tab, int i)
{
	tab->philosophers[i]->is_alive = 1;
	return (NULL);
}

void	philos_pthread_create(t_table *tab, int i)
{
	pthread_create(&tab->thread, NULL, control(tab, 0), NULL);
	while (tab->philosophers[i])
	{
		pthread_create(&tab->philosophers[i]->thread, NULL, routine(tab, i), NULL);
		i++;
	}
}
