/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:10:17 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/10 18:41:54 by lpupier          ###   ########.fr       */
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
 * @brief Function of freeing program memory and deleting mutexes.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	free_memory_and_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->list_philo[idx].access_philo);
		data->list_philo[idx].is_alive = 0;
		pthread_join(data->list_philo[idx].thread_id, NULL);
		pthread_mutex_unlock(&data->list_philo[idx].access_philo);
	}
	destroy_all_mutex(data);
	free(data->list_philo);
	free(data->list_forks);
}

/**
 * @brief Functions to check if all the philosophers have eaten
 * the minimum number of times if the mode is active.
 * 
 * @param data General structure of the program (see includes/philo.h).
 * @return (int) Returns 1 if all the philosophers have eaten
 * the minimum number of times. 0 otherwise or if the mode is not active. 
 */
int	check_everyone_eating_status(t_data *data)
{
	int	idx;
	int	status;

	status = 1;
	idx = -1;
	if (!data->nb_max_eat)
		return (0);
	while (++idx < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->list_philo[idx].access_philo);
		if (data->list_philo[idx].nb_of_time_eat < data->nb_max_eat)
			status = 0;
		pthread_mutex_unlock(&data->list_philo[idx].access_philo);
	}
	return (status);
}
