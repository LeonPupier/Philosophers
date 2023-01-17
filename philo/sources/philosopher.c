/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:25:59 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/17 15:13:14 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	text(t_philo *philo, char *str, char *color)
{
	printf("%s%.0fms%s \e[1m%d\e[0m%s %s\n", color,
		(double)philo->time_backup / 1000, color, philo->id, NC, str);
}

int	waiting(t_philo *philo, int time_to_wait)
{
	if (philo->time > time_to_wait)
	{
		if (philo->activitie == EATING)
			philo->activitie = SLEEPING;
		else if (philo->activitie == SLEEPING)
			philo->activitie = EATING;
		return (1);
	}
	return (0);
}

void	routine(t_philo *philo)
{
	static int	time_to_wait;

	if (philo->is_waiting)
	{
		if (waiting(philo, time_to_wait) == 1)
			philo->is_waiting = 0;
	}
	else if (philo->activitie == EATING)
	{
		//text(philo, "is thinking", YELLOW);
		text(philo, "is eating", BLUE);
		philo->time = 0;
		time_to_wait = philo->time_to_eat;
		philo->is_waiting = 1;
	}
	else if (philo->activitie == SLEEPING)
	{
		text(philo, "is sleeping", GREEN);
		time_to_wait = philo->time_to_sleep;
		philo->is_waiting = 1;
	}
}

void	*philosopher(void *void_philo)
{
	t_philo			*philo;
	struct timeval	current_time;

	philo = (t_philo *)void_philo;
	philo->activitie = SLEEPING;
	while (philo->time <= philo->time_to_die)
	{
		gettimeofday(&current_time, NULL);
		philo->time = (current_time.tv_sec - philo->data->init.tv_sec) \
		* 1000000 + current_time.tv_usec - philo->data->init.tv_usec;
		philo->time_backup = (current_time.tv_sec - philo->data->init.tv_sec) \
		* 1000000 + current_time.tv_usec - philo->data->init.tv_usec;
		routine(philo);
	}
	text(philo, "died", RED);
	philo->is_alive = 0;
	return (NULL);
}
