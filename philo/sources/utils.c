/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:22:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/07 15:09:34 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

/**
 * @brief Function allowing to display the project logs on the screen according
 * to the model requested with the possibility of adding color.
 * 
 * @param philo Structure of philosopher (see headers/philo.h).
 * @param str	The character string displayed on the screen.
 * @param color	The color in which to display certain text elements.
 */
void	text(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->data->display_text);
	printf("%s%.0f%s \e[1m%d\e[0m%s %s\n", color,
		(double)philo->time_backup / 1000, color, philo->id, NC, str);
	pthread_mutex_unlock(&philo->data->display_text);
}

/**
 * @brief Function to lock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see headers/philo.h).
 */
void	lock_forks_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (philo->id < philo->data->nb_of_philo)
		pthread_mutex_lock(&philo->data->list_philo[philo->id + 1].left_fork);
	else
		pthread_mutex_lock(&philo->data->list_philo[philo->id - 1].left_fork);
}

/**
 * @brief Function to unlock the mutexes represented by the 2 forks to
 * the left and the right of the philosopher.
 * 
 * @param philo	Structure of philosopher (see headers/philo.h).
 */
void	unlock_forks_to_eat(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	if (philo->id < philo->data->nb_of_philo)
		pthread_mutex_unlock(&philo->data->list_philo[philo->id + 1].left_fork);
	else
		pthread_mutex_unlock(&philo->data->list_philo[philo->id - 1].left_fork);
}

/**
 * @brief Function to destroy the entire mutex representing the
 * fork for each philosopher.
 * 
 * @param data General structure of the program (see headers/philo.h).
 */
void	destroy_all_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nb_of_philo)
		pthread_mutex_destroy(&data->list_philo[idx].left_fork);
	pthread_mutex_destroy(&data->display_text);
}
