/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:28:43 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/11 16:34:22 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function for launching threads representing each philosopher.
 * 
 * @param data General structure of the program (see includes/philo.h).
 * @return (int) EXIT_SUCCESS if all is well, EXIT_FAILURE otherwise.
 */
int	launch_threads(t_data *data)
{
	int	count;
	int	status;

	data->init_time = get_time();
	count = -1;
	while (++count < data->nb_of_philo)
	{
		data->list_philo[count].data = data;
		status = pthread_create(&data->list_philo[count].thread_id, NULL, \
		philosopher, (void *)&data->list_philo[count]);
		if (status)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Function checking the state of each philosopher
 * and controlling the end of the program in case of death.
 * 
 * @param data General structure of the program (see includes/philo.h).
 */
void	loop_of_life(t_data *data)
{
	int	running;
	int	idx;

	running = 1;
	while (running)
	{
		if (check_everyone_eating_status(data))
		{
			if (data->nb_max_eat)
				declare_everyone_dead(data);
			running = display_end_game(data);
		}
		idx = -1;
		while (++idx < data->nb_of_philo)
		{
			pthread_mutex_lock(&data->list_philo[idx].access_philo);
			if (data->list_philo[idx].is_alive == 0)
			{
				unsecure_text(&data->list_philo[idx], "died", RED);
				pthread_mutex_unlock(&data->list_philo[idx].access_philo);
				return ;
			}
			pthread_mutex_unlock(&data->list_philo[idx].access_philo);
		}
	}
}
