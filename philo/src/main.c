/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:16:39 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/15 13:17:23 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(char **argv, t_table *tab)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (EXIT_FAILURE);
		}
	}
	tab->philo_amount = ft_atoi(argv[1]);
	tab->death_time = ft_atoi(argv[2]);
	tab->eat_time = ft_atoi(argv[3]);
	tab->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		tab->nbr_eat = ft_atoi(argv[5]);
	else
		tab->nbr_eat = -1;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		return (prnt_err("indvalid number of arguments"));
	table	= malloc(sizeof(t_table));
	if (!table)
		return (prnt_err("malloc failed"));
	if (init_table(argv, table) == EXIT_FAILURE)
		return (free(table), prnt_err("invalid argument, they must be numbers"));
	free(table);
	return (EXIT_SUCCESS);
}
