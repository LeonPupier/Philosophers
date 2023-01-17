/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:37:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/17 13:05:07 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Define the header
#ifndef PHILO_H
# define PHILO_H

// Librairies
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

// Colors
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define BLUE	"\e[34m"
# define YELLOW	"\e[33m"
# define NC		"\e[0m"

// Activities
enum {
	THINKING,
	EATING,
	SLEEPING
};

// Prototype
struct	s_data;

// Philo structure
typedef struct s_philo {
	struct s_data	*data;
	pthread_t		thread_id;
	int				id;
	int				activitie;
	int				time;
	int				time_backup;
	int				time_to_eat;
	int				nb_of_time_eat;
	int				nb_max_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				is_alive;
	int				is_waiting;
}	t_philo;

// Main structure
typedef struct s_data {
	int				nb_of_philo;
	t_philo			*list_philo;
	int				nb_forks;
	struct timeval	init;
}	t_data;

// parameters.c

int		check_errors(int argc, char **argv);
int		assign_data(t_data *data, int argc, char **argv);

// philosopher.c

void	text(t_philo *philo, char *str, char *color);
void	*philosopher(void *void_philo);

// ft_atoi.c

int		ft_atoi(const char *str);

#endif