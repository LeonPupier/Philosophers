/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:37:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/21 08:51:57 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Define the header
#ifndef PHILO_H
# define PHILO_H

// Librairies
# include <unistd.h>
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
# define PINK	"\e[95m"
# define NC		"\e[0m"

// Errors status
# define ATOI_OVERFLOW	2147483649

enum e_errors {
	WRONG_NUMBER,
	TOO_MANY_PHILO,
	BAD_CONVERSION,
	MALLOC_ERROR,
	THREAD_ERROR,
	TIME_TOO_LOW
};

// Activities
enum e_activites {
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
	int				nb_of_time_eat;
	long			time;
	long			time_backup;
	long			time_begin;
	long			time_to_wait;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

// Main structure
typedef struct s_data {
	int				nb_of_philo;
	int				is_alive;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_max_eat;
	long			init_time;
	t_philo			*list_philo;
	pthread_mutex_t	*list_forks;
	pthread_mutex_t	data_mutex;
}	t_data;

// main.c

int		main(int argc, char **argv);

// parameters.c

int		check_errors(int argc, char **argv);
int		assign_data(t_data *data, int argc, char **argv);
void	assign_philo(t_data *data);

// threads_gestion.c

int		launch_threads(t_data *data);
void	wait_end_simulation(t_data *data);

// philosopher.c

void	*philosopher(void *void_philo);
int		routine(t_philo *philo);
int		fork_gestion_with_one_meal(t_philo *philo);

// activities.c

long	eating(t_philo *philo);
long	sleeping(t_philo *philo);
int		waiting(t_philo *philo);

// display.c

int		text(t_philo *philo, char *str, char *color);
void	unsecure_text(t_philo *philo, char *str, char *color);
int		display_end_game(t_data *data);
void	display_rules(void);
int		display_error(int code);

// mutex.c

void	init_all_mutex(t_data *data);
void	init_forks_of_philo(t_philo *philo);
int		lock_forks_to_eat(t_philo *philo);
void	unlock_forks_to_eat(t_philo *philo);
void	destroy_all_mutex(t_data *data);

// utils.c

long	get_time(void);
void	wait_all_philo_come_alive(t_philo *philo);
void	end_simulation_by_death(t_philo *philo);
void	free_memory_and_mutex(t_data *data);

// ft_atoi.c

long	ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

#endif