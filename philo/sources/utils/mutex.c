/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:22:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/21 08:47:29 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function to initalize the entire mutex representing the
 * fork for each philosopher, the access philo and the display mutex.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	init_all_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
		pthread_mutex_init(&data->list_forks[idx], NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
}

/**
 * @brief Function to initialize the addresses of the philosopher's
 * left and right forks.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 */
void	init_forks_of_philo(t_philo *philo)
{
	if (philo->data->nb_of_philo == 1)
		return ;
	if (philo->id % 2 == 1)
	{
		philo->left_fork = &philo->data->list_forks[philo->id];
		philo->right_fork = &philo->data->list_forks[\
		(philo->id + 1) % philo->data->nb_of_philo];
	}
	else
	{
		philo->left_fork = &philo->data->list_forks[\
		(philo->id + 1) % philo->data->nb_of_philo];
		philo->right_fork = &philo->data->list_forks[philo->id];
	}
}

/**
 * @brief Function to lock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 * @return (int) Returns 1 if the forks have been locked, 0 otherwise.
 */
int	lock_forks_to_eat(t_philo *philo)
{
	if (philo->data->nb_of_philo > 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!text(philo, "has taken a fork", PINK))
			return (pthread_mutex_unlock(philo->left_fork), 0);
		pthread_mutex_lock(philo->right_fork);
		if (!text(philo, "has taken a fork", PINK))
			return (unlock_forks_to_eat(philo), 0);
	}
	else
		return (end_simulation_by_death(philo), 0);
	return (1);
}

/**
 * @brief Function to unlock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 */
void	unlock_forks_to_eat(t_philo *philo)
{
	if (philo->data->nb_of_philo > 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

/**
 * @brief Function to destroy the entire mutex representing the
 * fork for each philosopher, the access philo and the display mutex.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	destroy_all_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
		pthread_mutex_destroy(&data->list_forks[idx]);
	pthread_mutex_destroy(&data->data_mutex);
}
