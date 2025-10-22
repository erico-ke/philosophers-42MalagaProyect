/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:16:39 by erico-ke          #+#    #+#             */
/*   Updated: 2025/10/22 15:09:34 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(t_table *tab, char **argv)
{
	if (tab->philo_amount <= 0)
		return (prnt_err("Philosopher amount must be bigger than 0"));
	if (tab->death_time < 0)
		return (prnt_err("Death time can't be negative"));
	if (tab->eat_time <= 0)
		return (prnt_err("Time to eat must be bigger than 0"));
	if (tab->sleep_time <= 0)
		return (prnt_err("Time to sleep must be bigger than 0"));
	if (!argv[5])
		return (EXIT_SUCCESS);
	else if (tab->nbr_eat < 0)
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
	tab->philo_amount = ft_atol(argv[1]);
	tab->death_time = ft_atol(argv[2]);
	tab->eat_time = ft_atol(argv[3]);
	tab->sleep_time = ft_atol(argv[4]);
	if (argv[5])
		tab->nbr_eat = ft_atol(argv[5]);
	else
		tab->nbr_eat = -1;
	tab->death_flag = 0;
	return (EXIT_SUCCESS);
}

static int	init_and_validate(char **argv, t_table *tab)
{
	if (init_table(argv, tab) == EXIT_FAILURE)
		return (free(tab), prnt_err("invalid argument, only positive numbers"));
	if (check_values(tab, argv) == EXIT_FAILURE)
		return (free(tab), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	*tab;

	if (argc < 5 || argc > 6)
		return (prnt_err("invalid number of arguments"));
	tab = malloc(sizeof(t_table));
	if (!tab)
		return (prnt_err("malloc failed"));
	if (init_and_validate(argv, tab) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_start_time(tab);
	if (tab->philo_amount == 1)
	{
		philo_routine(tab);
		free(tab);
		return (EXIT_SUCCESS);
	}
	if (philo_pthread_init(tab, -1) == EXIT_FAILURE)
		return (t_philo_free(tab, 0), EXIT_FAILURE);
	philos_pthread_create(tab, -1);
	philos_pthread_join(tab);
	t_philo_free(tab, 0);
	return (EXIT_SUCCESS);
}
