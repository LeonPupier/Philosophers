/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:34:09 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/11 14:40:25 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function used to feed the philosopher passed as a parameter.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @return (long) Returns the waiting time a philosopher takes to eat.
 * 0 if the philosopher is supposed to be dead between two function calls.
 */
long	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->access_philo);
	if (!philo->is_alive)
		return (pthread_mutex_unlock(&philo->access_philo), 0);
	text(philo, "is thinking", BLUE);
	pthread_mutex_unlock(&philo->access_philo);
	lock_forks_to_eat(philo);
	philo->time = get_time();
	philo->time_backup = philo->time;
	if (philo->time - philo->time_backup > philo->data->time_to_die)
		return (unlock_forks_to_eat(philo), 0);
	text(philo, "is eating", GREEN);
	pthread_mutex_lock(&philo->access_philo);
	philo->nb_of_time_eat++;
	philo->is_waiting = 1;
	pthread_mutex_unlock(&philo->access_philo);
	return (philo->data->time_to_eat);
}

/**
 * @brief Function used to put the philosopher to sleep passed as a parameter.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @return (long) Returns the waiting time a philosopher takes to eat.
 * 0 if the philosopher is supposed to be dead between two function calls.
 */
long	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->access_philo);
	if (!philo->is_alive)
		return (pthread_mutex_unlock(&philo->access_philo), 0);
	text(philo, "is sleeping", YELLOW);
	pthread_mutex_unlock(&philo->access_philo);
	philo->is_waiting = 1;
	return (philo->data->time_to_sleep);
}

/**
 * @brief Function to make the past philosopher wait in parameter
 * the given time.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @param time_to_wait The time to wait in milliseconds.
 * @return (int) Returns 1 if the wait is over, 0 otherwise.
 */
int	waiting(t_philo *philo, long time_to_wait)
{
	if (!philo->time_begin)
		philo->time_begin = philo->time;
	if (philo->time - philo->time_begin > time_to_wait)
	{
		if (philo->activitie == EATING)
		{
			pthread_mutex_lock(&philo->access_philo);
			if (philo->is_alive)
				unlock_forks_to_eat(philo);
			pthread_mutex_unlock(&philo->access_philo);
			philo->activitie = SLEEPING;
		}
		else if (philo->activitie == SLEEPING)
			philo->activitie = EATING;
		philo->is_waiting = 0;
		philo->time_begin = 0;
		return (1);
	}
	return (0);
}
