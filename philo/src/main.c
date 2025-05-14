/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:16:39 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/14 16:52:38 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(char **argv)
{
	
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 4 || argc > 5)
		return (prnt_err("indvalid number of arguments"));
	table	= malloc(sizeof(t_table));
	if (!table)
		return (prnt_err("malloc failed"));
	if (init_table(argv) == EXIT_FAILURE)
		return (prnt_err("balls"));
}