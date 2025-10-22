/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:45:32 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 15:11:13 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	int		neg;

	i = 0;
	res = 0;
	neg = 1;
	while (nptr[i] == (' ') || nptr[i] == ('\f') || nptr[i] == ('\n')
		|| nptr[i] == ('\r') || nptr[i] == ('\t') || nptr[i] == ('\v'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = (-neg);
		i++;
	}
	while (nptr[i])
	{
		if (ft_isdigit(nptr[i]))
			res = (res * 10) + (nptr[i] - 48);
		else
			break ;
		i++;
	}
	return (res * neg);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

void	philos_pthread_join(t_table *tab)
{
	int	i;

	i = -1;
	while (++i < tab->philo_amount)
		pthread_join(tab->philosophers[i]->thread, NULL);
	pthread_join(tab->thread, NULL);
}
