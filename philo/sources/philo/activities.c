/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:34:09 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/20 16:20:42 by lpupier          ###   ########.fr       */
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
	if (!text(philo, "is thinking", BLUE))
		return (0);
	if (!lock_forks_to_eat(philo))
		return (0);
	philo->time = get_time();
	if (philo->time - philo->time_backup >= philo->data->time_to_die)
		return (unlock_forks_to_eat(philo), 0);
	philo->time_backup = philo->time;
	if (!text(philo, "is eating", GREEN))
		return (unlock_forks_to_eat(philo), 0);
	philo->nb_of_time_eat++;
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
	if (!text(philo, "is sleeping", YELLOW))
		return (0);
	return (philo->data->time_to_sleep);
}

/**
 * @brief Function to make the past philosopher wait in parameter
 * the given time.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @return (int) Returns 1 if the wait goes as expected, 0 otherwise.
 */
int	waiting(t_philo *philo)
{
	if (get_time() - philo->time_backup >= philo->data->time_to_die)
		return (0);
	if (!philo->time_begin)
		philo->time_begin = get_time();
	if (get_time() - philo->time_begin >= philo->time_to_wait)
	{
		if (philo->activitie == EATING)
		{
			unlock_forks_to_eat(philo);
			philo->activitie = SLEEPING;
		}
		else if (philo->activitie == SLEEPING)
			philo->activitie = EATING;
		philo->time_to_wait = 0;
		philo->time_begin = 0;
	}
	return (1);
}
