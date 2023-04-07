/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:25:59 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/07 13:32:57 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philosopher(void *void_philo)
{
	t_philo			*philo;
	struct timeval	current_time;
	int				time_gap;

	philo = (t_philo *)void_philo;
	philo->activitie = EATING;
	gettimeofday(&current_time, NULL);
	time_gap = current_time.tv_usec - philo->data->init.tv_usec;
	philo->time_backup += time_gap;
	philo->time_reset = 0;
	while (philo->time <= philo->data->time_to_die + time_gap)
	{
		gettimeofday(&current_time, NULL);
		philo->time = (current_time.tv_sec - philo->data->init.tv_sec) \
		* 1000000 + current_time.tv_usec - philo->data->init.tv_usec \
		+ time_gap - philo->time_reset;
		philo->time_backup = (current_time.tv_sec - philo->data->init.tv_sec) \
		* 1000000 + current_time.tv_usec - philo->data->init.tv_usec + time_gap;
		routine(philo);
	}
	text(philo, "died", RED);
	philo->is_alive = 0;
	return (NULL);
}

void	routine(t_philo *philo)
{
	static int	time_to_wait;

	if (philo->is_waiting)
		waiting(philo, time_to_wait);
	else if (philo->activitie == EATING)
		time_to_wait = eating(philo);
	else if (philo->activitie == SLEEPING)
		time_to_wait = sleeping(philo);
}

int	waiting(t_philo *philo, int time_to_wait)
{
	static int	begin_time;

	if (!begin_time)
		begin_time = philo->time;
	if (philo->time - begin_time > time_to_wait)
	{
		if (philo->activitie == EATING)
		{
			unlock_forks_to_eat(philo);
			philo->activitie = SLEEPING;
		}
		else if (philo->activitie == SLEEPING)
			philo->activitie = EATING;
		philo->is_waiting = 0;
		begin_time = 0;
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	text(philo, "is thinking", BLUE);
	lock_forks_to_eat(philo);
	text(philo, "is eating", GREEN);
	philo->nb_of_time_eat += 1;
	philo->time_reset = philo->time_backup;
	philo->is_waiting = 1;
	return (philo->data->time_to_eat);
}

int	sleeping(t_philo *philo)
{
	text(philo, "is sleeping", YELLOW);
	philo->is_waiting = 1;
	return (philo->data->time_to_sleep);
}
