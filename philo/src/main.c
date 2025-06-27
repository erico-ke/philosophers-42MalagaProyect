/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:16:39 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/27 15:14:51 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(t_table *tab)
{
	if (tab->philo_amount <= 0)
		return (prnt_err("Philosopher amount must be bigger than 0"));
	if (tab->death_time < 0)
		return (prnt_err("Death time can't be negative"));
	if (tab->eat_time <= 0)
		return (prnt_err("Time to eat must be bigger than 0"));
	if (tab->sleep_time <= 0)
		return (prnt_err("Time to sleep must be bigger than 0"));
	if (tab->nbr_eat < 0)
			return (prnt_err("Times to eat must be bigger than 0"));
	return (EXIT_SUCCESS);
}

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
	tab->philo_amount = ft_atoi(argv[1]);//estos atoi en realidad deberian ser algo como atol pq los numeros vienen en milisegundos
	tab->death_time = ft_atoi(argv[2]);
	tab->eat_time = ft_atoi(argv[3]);
	tab->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		tab->nbr_eat = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	*tab;

	if (argc < 5 || argc > 6)
		return (prnt_err("indvalid number of arguments"));
	tab = malloc(sizeof(t_table));
	if (!tab)
		return (prnt_err("malloc failed"));
	if (init_table(argv, tab) == EXIT_FAILURE)
		return (free(tab), prnt_err("invalid argument, they must be positive numbers"));
	if (check_values(tab) == EXIT_FAILURE)
		return (free(tab), EXIT_FAILURE);
	if (tab->philo_amount == 1)
		philo_routine(tab);
	else
	{
		
	}
	free(tab);
	return (EXIT_SUCCESS);
}
