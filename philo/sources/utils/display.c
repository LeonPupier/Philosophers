/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:19:02 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/20 14:28:02 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Function allowing to display the project logs on the screen according
 * to the model requested with the possibility of adding color.
 * 
 * @param philo Structure of philosopher (see includes/philo.h).
 * @param str	The character string displayed on the screen.
 * @param color	The color in which to display certain text elements.
 * @return (int) returns 1 if the display has been performed, 0 otherwise.
 */
int	text(t_philo *philo, char *str, char *color)
{
	philo->time = get_time();
	if (philo->time - philo->time_backup >= philo->data->time_to_die)
		return (0);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->is_alive)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (0);
	}
	printf("%s%ld%s \e[1m%d\e[0m%s %s\n", color, get_time() \
	- philo->data->init_time, color, philo->id + 1, NC, str);
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (1);
}

/**
 * @brief Function allowing to display the project logs on the screen according
 * to the model requested with the possibility of adding color.
 * (Equivalent to the text() function without checking
 * if the philosopher is alive or not and the data mutex.
 * 
 * @param philo	Structure of philosopher (see includes/philo.h).
 * @param str	The character string displayed on the screen.
 * @param color	The color in which to display certain text elements.
 */
void	unsecure_text(t_philo *philo, char *str, char *color)
{
	printf("%s%ld%s \e[1m%d\e[0m%s %s\n", color, get_time() \
	- philo->data->init_time, color, philo->id + 1, NC, str);
}

/**
 * @brief Function to display the end of program message if all
 * the philosophers have eaten the number provided as an argument.
 * 
 * @param data General structure of the program (see includes/philo.h).
 * @return (int) Returns 1 in success, 0 otherwise.
 */
int	display_end_game(t_data *data)
{
	if (!data->nb_max_eat)
		return (0);
	pthread_mutex_lock(&data->data_mutex);
	if (data->nb_max_eat > 1)
		printf("%s[END] All philosophers have eaten at least %d times.%s\n", \
		RED, data->nb_max_eat, NC);
	else
		printf("%s[END] All philosophers have eaten at least %d time.%s\n", \
		RED, data->nb_max_eat, NC);
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}

/**
 * @brief Display of program argument formatting rules.
 * 
 */
void	display_rules(void)
{
	printf("\e[4mBad arguments, expected:\e[0m\n");
	printf("◦ The number of philosophers.\n◦ Time for a philo");
	printf(" %sto die\e[0m if he hasn't started eating.\n", RED);
	printf("◦ The time it takes for a philosopher %sto eat\e[0m.\n", GREEN);
	printf("◦ The time a philosopher will spend %ssleeping\e[0m.\n", YELLOW);
	printf("\e[1m--Optionnal:\e[0m\n");
	printf("◦ Stops if all the philo have eaten the given number.\n");
	printf("\e[2m(Infos) All times must be given in milliseconds.\e[22m\n");
}

/**
 * @brief Function for displaying an explicit error message 
 * regarding the error triggered.
 * 
 * @param code Error code for defined display. 
 * @return (int) Returns 1 if the error is known, 0 otherwise.
 */
int	display_error(int code)
{
	if (code == WRONG_NUMBER)
		printf("%s[ERROR] Wrong number of arguments.%s\n", RED, NC);
	else if (code == TOO_MANY_PHILO)
		printf("%s[WARNING] Too many philosophers (> 200).%s\n", RED, NC);
	else if (code == TIME_TOO_LOW)
		printf("%s[WARNING] Time too small (< 60ms).%s\n", RED, NC);
	else if (code == BAD_CONVERSION)
	{
		printf("%s[ERROR] Overflow, negative or null ", RED);
		printf("value on an argument.%s\n", NC);
	}
	else if (code == MALLOC_ERROR)
		printf("%s[ERROR] Malloc error.%s\n", RED, NC);
	else if (code == THREAD_ERROR)
		printf("%s[ERROR] Thread initialization error.%s\n", RED, NC);
	else
		return (0);
	return (1);
}
