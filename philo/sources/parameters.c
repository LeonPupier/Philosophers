/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:38:36 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/07 14:28:45 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

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
	int	count;
	int	error;

	error = 0;
	if (argc != 5 && argc != 6)
		error = 1;
	count = 0;
	while (++count < argc)
	{
		if (ft_atoi(argv[count]) <= 0)
			error = 1;
	}
	if (error == 1)
	{
		printf("\033[31m[ERROR]\033[00m	\e[4mBad arguments, expected:\e[0m\n");
		printf("◦ The number of philosophers.\n◦ Time for a philo");
		printf(" %sto die\e[0m if he hasn't started eating.\n", RED);
		printf("◦ The time it takes for a philosopher %sto eat\e[0m.\n", GREEN);
		printf("◦ The time a philosopher will spend %ssleeping\e[0m.\n", YELLOW);
		printf("\e[1m--Optionnal:\e[0m\n");
		printf("◦ Stops if all the philo have eaten the given number.\n");
		printf("\e[2m(Infos) All times must be given in milliseconds.\e[22m\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Function for assigning starting values ​​for each philosopher
 * and filling in the (t_data) data structure.
 * 
 * @param data General structure of the program (see headers/philo.h).
 * @param argc Number of program arguments supplied at runtime.
 * @param argv Array of character strings corresponding to the arguments passed.
 * @return (int) Returns the exit status of the function,
 * EXIT_SUCCESS or EXIT_FAILURE.
 */
int	assign_data(t_data *data, int argc, char **argv)
{
	int	count;

	data->nb_of_philo = ft_atoi(argv[1]);
	data->list_philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (data->list_philo == NULL)
		return (EXIT_FAILURE);
	count = -1;
	while (++count < data->nb_of_philo)
	{
		data->list_philo[count].id = count + 1;
		if (argc == 6)
			data->list_philo[count].nb_max_eat = ft_atoi(argv[5]);
		else
			data->list_philo[count].nb_max_eat = 0;
		data->list_philo[count].nb_of_time_eat = 0;
		data->list_philo[count].is_waiting = 0;
		data->list_philo[count].is_alive = 1;
		data->list_philo[count].time = 0;
		pthread_mutex_init(&data->list_philo[count].left_fork, NULL);
	}
	return (EXIT_SUCCESS);
}
