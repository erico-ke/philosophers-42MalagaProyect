/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:35:06 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/01 11:40:26 by erico-ke         ###   ########.fr       */
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
	while (tab->philosophers[i])
	{
		if (tab->philosophers[i]->r_fork)
			pthread_mutex_destroy(tab->philosophers[i]->r_fork);
		free(tab->philosophers[i]);
		i++;
	}
	free(tab);
}
