/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:59 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/04 17:01:07 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_mutex_init(t_table *tab)
{
	if (pthread_mutex_init(tab->writer, NULL) == -1)
			return (EXIT_FAILURE);
}

void	print_mutex_use(t_table *tab, char *msg)
{
	
}
