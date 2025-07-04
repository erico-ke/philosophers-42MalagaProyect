/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:17:01 by erico-ke          #+#    #+#             */
/*   Updated: 2025/07/04 17:01:43 by erico-ke         ###   ########.fr       */
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

typedef struct table	t_table;

typedef struct philo
{
	int				id;
	int				is_eating;
	int				last_time_eated;
	int				is_sleeping;
	int				is_alive;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	t_table			*tab;
} t_philo;

typedef	struct table
{
	int				death_flag;
	int				philo_amount;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	int				nbr_eat;
	pthread_t		thread;
	pthread_mutex_t	*writer;
	t_philo			**philosophers;
} t_table;

/* Error management and memory free */
int		prnt_err(char *str);
void	free_splt(char **split);
void	t_philo_free(t_table *tab, int i);

/* Utils */
long	ft_atol(const char *nptr);
int		ft_isdigit(int c);

/* Philosophers */
void	philo_routine(t_table *tab);
int		philo_pthread_init(t_table *tab, int i);
void	philos_pthread_create(t_table *tab, int i);
void	philos_pthread_join(t_table *tab);

#endif