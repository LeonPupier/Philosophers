/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:19:02 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/10 14:33:21 by lpupier          ###   ########.fr       */
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
 */
void	text(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->data->display_text);
	printf("%s%ld%s \e[1m%d\e[0m%s %s\n", color, philo->time \
	- philo->data->init_time, color, philo->id, NC, str);
	pthread_mutex_unlock(&philo->data->display_text);
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
		printf("%s[ERROR] Too many philosophers (> 256).%s\n", RED, NC);
	else if (code == BAD_CONVERSION)
	{
		printf("%s[ERROR] Overflow, negative or null ", RED);
		printf("value on an argument.%s\n", NC);
	}
	else if (code == MALLOC_ERROR)
		printf("%s[ERROR] Malloc error.%s\n", RED, NC);
	else
		return (0);
	return (1);
}
