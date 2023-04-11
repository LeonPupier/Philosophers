/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:22:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/11 15:56:14 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function to initalize the entire mutex representing the
 * fork for each philosopher and the display mutex.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	init_all_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
	{
		pthread_mutex_init(&data->list_forks[idx], NULL);
		pthread_mutex_init(&data->list_philo[idx].access_philo, NULL);
	}
	pthread_mutex_init(&data->display_text, NULL);
}

/**
 * @brief Function to lock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 */
void	lock_forks_to_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->data->list_forks[philo->id]);
	if (philo->id > 1)
		pthread_mutex_lock(&philo->data->list_forks[philo->id - 1]);
	else if (philo->id == philo->data->nb_of_philo)
		pthread_mutex_lock(&philo->data->list_forks[0]);
	else
		pthread_mutex_lock(\
		&philo->data->list_forks[philo->data->nb_of_philo - 1]);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->data->list_forks[philo->id]);
}

/**
 * @brief Function to unlock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 */
void	unlock_forks_to_eat(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->list_forks[philo->id]);
	if (philo->id > 1)
		pthread_mutex_unlock(&philo->data->list_forks[philo->id - 1]);
	else if (philo->id == philo->data->nb_of_philo)
		pthread_mutex_unlock(&philo->data->list_forks[0]);
	else
		pthread_mutex_unlock(\
		&philo->data->list_forks[philo->data->nb_of_philo - 1]);
}

/**
 * @brief Function to destroy the entire mutex representing the
 * fork for each philosopher and the display mutex.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	destroy_all_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->list_forks[idx]);
		pthread_mutex_destroy(&data->list_philo[idx].access_philo);
	}
	pthread_mutex_destroy(&data->display_text);
}
