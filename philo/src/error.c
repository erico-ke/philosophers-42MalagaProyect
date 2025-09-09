/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:35:06 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/09 17:49:06 by erico-ke         ###   ########.fr       */
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

void	t_philo_free(t_table *tab, int i)
{
	if (!tab)
		return ;
	if (tab->philosophers)
	{
		while (i < tab->philo_amount)
		{
			if (tab->philosophers[i])
			{
				if (tab->philosophers[i]->l_fork)
				{
					pthread_mutex_destroy(tab->philosophers[i]->l_fork);
					free(tab->philosophers[i]->l_fork);
				}
				free(tab->philosophers[i]);
			}
			i++;
		}
		free(tab->philosophers);
	}
	pthread_mutex_destroy(tab->writer);
	free(tab->writer);
	pthread_mutex_destroy(tab->alive);
	free(tab->alive);
	free(tab);
}
