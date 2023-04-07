/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:37:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/07 15:07:19 by lpupier          ###   ########.fr       */
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
	int				time_reset;
	int				nb_of_time_eat;
	int				nb_max_eat;
	int				is_waiting;
	int				is_alive;
	pthread_mutex_t	left_fork;
}	t_philo;

// Main structure
typedef struct s_data {
	int				nb_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	t_philo			*list_philo;
	pthread_mutex_t	display_text;
	struct timeval	init;
}	t_data;

// main.c

int		main(int argc, char **argv);
int		loop_of_life(t_data *data);

// parameters.c

int		check_errors(int argc, char **argv);
int		assign_data(t_data *data, int argc, char **argv);

// philosopher.c

void	*philosopher(void *void_philo);
void	routine(t_philo *philo);
int		waiting(t_philo *philo, int time_to_wait);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);

// utils.c

void	text(t_philo *philo, char *str, char *color);
void	lock_forks_to_eat(t_philo *philo);
void	unlock_forks_to_eat(t_philo *philo);
void	destroy_all_mutex(t_data *data);

// ft_atoi.c

int		ft_atoi(const char *str);

#endif