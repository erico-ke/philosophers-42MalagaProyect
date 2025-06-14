/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:17:01 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/09 14:40:31 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef	struct table
{
	int			philo_amount;
	long long	death_time;
	long long	eat_time;
	long long	sleep_time;
	int			nbr_eat;
	t_philo		**philosophers;
} t_table;

typedef struct philo
{
	int	is_eating;
	int	last_time_eated;
	int	is_sleeping;
	int	is_alive;
} t_philo;


/* Error management and memory free */
int		prnt_err(char *str);
void	free_splt(char **split);

/* Utils */
int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

#endif