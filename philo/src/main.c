/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:16:39 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/09 13:06:53 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(t_table *tab)
{
	if (tab->philo_amount <= 0)
		return (prnt_err(""));
	if (tab->death_time < 0)
		return (prnt_err(""));
	if (tab->eat_time <= 0)
		return (prnt_err(""));
	if (tab->sleep_time <= 0)
		return (prnt_err(""));
	if (tab->nbr_eat /* crear condicion para que no sea ni menor ni igual a 0 pero
		 teniendo en cuenta que estamos seteando el numero a -1 cuando no hay 5to input, entonces 
		 hay que ser conscientes de que si ingresan un -1 nos jodimos*/)
			return (prnt_err(""));
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
	else
		tab->nbr_eat = -1;
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
		return (free(tab), prnt_err("invalid argument, they must be numbers"));
	
	free(tab);
	return (EXIT_SUCCESS);
}
