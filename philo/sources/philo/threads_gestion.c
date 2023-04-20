/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:28:43 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/20 13:33:01 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function for launching threads representing each philosopher.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	launch_threads(t_data *data)
{
	int	count;

	data->init_time = 0;
	count = -1;
	while (++count < data->nb_of_philo)
	{
		pthread_create(&data->list_philo[count].thread_id, NULL, \
		philosopher, (void *)&data->list_philo[count]);
	}
	pthread_mutex_lock(&data->data_mutex);
	data->init_time = get_time();
	pthread_mutex_unlock(&data->data_mutex);
}

/**
 * @brief function to wait for the end of the simulation
 * and display the appropriate message if necessary.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	wait_end_simulation(t_data *data)
{
	int	idx;
	int	eating_status;

	idx = -1;
	while (++idx < data->nb_of_philo)
		pthread_join(data->list_philo[idx].thread_id, NULL);
	eating_status = 1;
	idx = -1;
	while (++idx < data->nb_of_philo)
	{
		if (data->list_philo[idx].nb_of_time_eat < data->nb_max_eat)
			eating_status = 0;
	}
	if (eating_status && data->nb_max_eat)
		display_end_game(data);
}
