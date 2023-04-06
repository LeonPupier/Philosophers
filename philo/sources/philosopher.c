/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:25:59 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/06 18:01:40 by lpupier          ###   ########.fr       */
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
	static int	begin_time;

	if (!begin_time)
		begin_time = philo->time;
	if (philo->time - begin_time > time_to_wait)
	{
		if (philo->activitie == EATING)
			philo->activitie = SLEEPING;
		else if (philo->activitie == SLEEPING)
			philo->activitie = EATING;
		philo->is_waiting = 0;
		begin_time = 0;
		return (1);
	}
	return (0);
}

void	routine(t_philo *philo)
{
	static int	time_to_wait;

	if (philo->is_waiting)
		waiting(philo, time_to_wait);
	else if (philo->activitie == EATING)
	{
		text(philo, "is eating", GREEN);
		philo->time_reset = philo->time_backup;
		time_to_wait = philo->time_to_eat;
		philo->is_waiting = 1;
	}
	else if (philo->activitie == SLEEPING)
	{
		text(philo, "is sleeping", YELLOW);
		time_to_wait = philo->time_to_sleep;
		philo->is_waiting = 1;
	}
}

void	*philosopher(void *void_philo)
{
	t_philo			*philo;
	struct timeval	current_time;
	int				time_gap;

	philo = (t_philo *)void_philo;
	philo->activitie = SLEEPING;
	gettimeofday(&current_time, NULL);
	time_gap = current_time.tv_usec - philo->data->init.tv_usec;
	philo->time_backup += time_gap;
	philo->time_reset = 0;
	text(philo, "is born", BLUE);
	while (philo->time <= philo->time_to_die + time_gap)
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
