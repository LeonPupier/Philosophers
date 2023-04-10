/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:38:36 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/10 18:26:33 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Function called at the beginning of the program to check if the format
 * of the arguments provided at the execution of the program is correct.
 * 
 * @param argc Number of program arguments supplied at runtime.
 * @param argv Array of character strings corresponding to the arguments passed.
 * @return (int) Returns the exit status of the function,
 * EXIT_SUCCESS or EXIT_FAILURE.
 */
int	check_errors(int argc, char **argv)
{
	int		count;
	long	number;
	int		error;

	error = 0;
	if (argc != 5 && argc != 6)
		error = display_error(WRONG_NUMBER);
	if (ft_atoi(argv[1]) > 256)
		error = display_error(TOO_MANY_PHILO);
	count = 0;
	while (++count < argc)
	{
		number = ft_atoi(argv[count]);
		if (number == ATOI_OVERFLOW || number < 1)
			error = display_error(BAD_CONVERSION);
	}
	if (error)
		return (display_rules(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Function for assigning starting values ​​for each philosopher
 * and filling in the (t_data) data structure.
 * 
 * @param data General structure of the program (see includes/philo.h).
 * @param argc Number of program arguments supplied at runtime.
 * @param argv Array of character strings corresponding to the arguments passed.
 * @return (int) Returns the exit status of the function,
 * EXIT_SUCCESS or EXIT_FAILURE.
 */
int	assign_data(t_data *data, int argc, char **argv)
{
	int	count;

	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_max_eat = ft_atoi(argv[5]);
	data->list_philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->list_philo)
		return (display_error(MALLOC_ERROR), EXIT_FAILURE);
	data->list_forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->list_forks)
	{
		free(data->list_philo);
		return (display_error(MALLOC_ERROR), EXIT_FAILURE);
	}
	count = -1;
	while (++count < data->nb_of_philo)
	{
		data->list_philo[count].id = count + 1;
		data->list_philo[count].is_alive = 1;
		data->list_philo[count].activitie = EATING;
	}
	return (EXIT_SUCCESS);
}
