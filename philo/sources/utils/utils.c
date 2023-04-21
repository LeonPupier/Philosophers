/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:10:17 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/21 09:51:02 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function to retrieve the current time in milliseconds
 * since the Epoch (see time(2)).
 * 
 * @return (long) Returns the current number of milliseconds.
 */
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Function serving as a wait for all the philosophers as long as they
 * are not all launched to avoid the lag.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 */
void	wait_all_philo_come_alive(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->init_time)
			break ;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}

/**
 * @brief Function to declare the end of the simulation by telling the other
 * philosophers that they must kill themselves and display the first death.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 */
void	end_simulation_by_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->is_alive)
	{
		philo->data->is_alive = 0;
		unsecure_text(philo, "died", RED);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}

/**
 * @brief Function of freeing program memory and deleting mutexes.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	free_memory_and_mutex(t_data *data)
{
	destroy_all_mutex(data);
	free(data->list_forks);
	free(data->list_philo);
}
