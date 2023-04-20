/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:25:59 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/20 16:30:16 by lpupier          ###   ########.fr       */
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
	init_forks_of_philo(philo);
	wait_all_philo_come_alive(philo);
	philo->time_backup = get_time();
	while (philo->nb_of_time_eat < philo->data->nb_max_eat \
	|| !philo->data->nb_max_eat)
	{
		if (!routine(philo))
		{
			end_simulation_by_death(philo);
			break ;
		}
	}
	fork_gestion_with_one_meal(philo);
	if (philo->time_to_wait && philo->activitie == EATING)
		unlock_forks_to_eat(philo);
	return (NULL);
}

/**
 * @brief Routine function of the philosopher so that
 * he can Eat, Sleep and Think.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @return (int) Returns 1 if the routine went well, 0 otherwise.
 */
int	routine(t_philo *philo)
{
	if (philo->time_to_wait)
	{
		if (!waiting(philo))
			return (0);
	}
	else
	{
		if (philo->activitie == EATING)
			philo->time_to_wait = eating(philo);
		else if (philo->activitie == SLEEPING)
			philo->time_to_wait = sleeping(philo);
		if (!philo->time_to_wait)
			return (0);
	}
	return (1);
}

/**
 * @brief Function to make a philosopher wait if the number of meals
 * he had to eat is 1 so that the following do not eat too quickly.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @return (int) Returns 1 if the philosopher had to distribute his forks well,
 * 0 if he did not need them.
 */
int	fork_gestion_with_one_meal(t_philo *philo)
{
	if (philo->data->nb_max_eat == 1)
	{
		while (philo->time_to_wait)
		{
			philo->time = get_time();
			waiting(philo);
		}
		return (1);
	}
	return (0);
}
