/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:25:59 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/10 18:38:22 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function of the philosopher heart with its loop
 * of routine and activity (Eat, Sleep, Think...).
 * 
 * @param void_philo Retrieval of the philosopher structure by the thread. 
 * @return (void*) Returns NULL in all cases.
 */
void	*philosopher(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->id > 1)
		usleep(5);
	philo->time_backup = get_time();
	while (philo->is_alive)
	{
		philo->time = get_time();
		if (philo->time - philo->time_backup <= philo->data->time_to_die)
			routine(philo);
		else
		{
			pthread_mutex_lock(&philo->access_philo);
			philo->is_alive = 0;
			pthread_mutex_unlock(&philo->access_philo);
		}
	}
	return (NULL);
}

/**
 * @brief Routine function of the philosopher so that
 * he can Eat, Sleep and Think.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 */
void	routine(t_philo *philo)
{
	if (philo->is_waiting)
		waiting(philo, philo->time_to_wait);
	else if (philo->activitie == EATING)
		philo->time_to_wait = eating(philo);
	else if (philo->activitie == SLEEPING)
		philo->time_to_wait = sleeping(philo);
}
