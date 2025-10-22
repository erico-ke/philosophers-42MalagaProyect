/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:35:06 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 15:09:34 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prnt_err(char *str)
{
	printf("Error, %s.\n", str);
	return (EXIT_FAILURE);
}

void	free_splt(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	free_philo(t_philo *philo)
{
	if (philo->l_fork)
	{
		pthread_mutex_destroy(philo->l_fork);
		free(philo->l_fork);
	}
	if (philo->meal_lock)
	{
		pthread_mutex_destroy(philo->meal_lock);
		free(philo->meal_lock);
	}
	free(philo);
}

void	t_philo_free(t_table *tab, int i)
{
	if (!tab)
		return ;
	if (tab->philosophers)
	{
		while (i < tab->philo_amount)
		{
			if (tab->philosophers[i])
				free_philo(tab->philosophers[i]);
			i++;
		}
		free(tab->philosophers);
	}
	if (tab->writer)
		pthread_mutex_destroy(tab->writer);
	if (tab->death)
		pthread_mutex_destroy(tab->death);
	free(tab->writer);
	free(tab->death);
	free(tab);
}
