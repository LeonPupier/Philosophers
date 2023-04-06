/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:38:36 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/06 14:03:13 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

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
		printf("◦ The number of philosophers.\n");
		printf("◦ Time for a philo to die if he hasn't started eating.\n");
		printf("◦ The time it takes for a philosopher to eat.\n");
		printf("◦ The time a philosopher will spend sleeping.\n");
		printf("\e[1m--Optionnal:\e[0m\n");
		printf("◦ Stops if all the philo have eaten the given number.\n");
		printf("\e[2m(Infos) All times must be given in milliseconds.\e[22m\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
		data->list_philo[count].time_to_die = ft_atoi(argv[2]) * 1000;
		data->list_philo[count].time_to_eat = ft_atoi(argv[3]) * 1000;
		data->list_philo[count].time_to_sleep = ft_atoi(argv[4]) * 1000;
		if (argc == 6)
			data->list_philo[count].nb_max_eat = ft_atoi(argv[5]);
		else
			data->list_philo[count].nb_max_eat = 0;
		data->list_philo[count].nb_of_time_eat = 0;
		data->list_philo[count].is_waiting = 0;
		data->list_philo[count].is_alive = 1;
		data->list_philo[count].time = 0;
	}
	return (EXIT_SUCCESS);
}
