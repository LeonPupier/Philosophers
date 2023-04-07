/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:33:58 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/07 15:08:54 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		count;

	if (check_errors(argc, argv))
		return (EXIT_FAILURE);
	if (assign_data(&data, argc, argv))
		return (EXIT_FAILURE);
	data.time_to_die = ft_atoi(argv[2]) * 1000;
	data.time_to_eat = ft_atoi(argv[3]) * 1000;
	data.time_to_sleep = ft_atoi(argv[4]) * 1000;
	pthread_mutex_init(&data.display_text, NULL);
	gettimeofday(&data.init, NULL);
	count = -1;
	while (++count < data.nb_of_philo)
	{
		data.list_philo[count].data = &data;
		pthread_create(&data.list_philo[count].thread_id, NULL, \
		philosopher, (void *)&data.list_philo[count]);
	}
	loop_of_life(&data);
	return (EXIT_SUCCESS);
}

int	loop_of_life(t_data *data)
{
	int	running;

	running = 1;
	while (running)
		(void)data;
	destroy_all_mutex(data);
	pthread_mutex_destroy(&data->display_text);
	free(data->list_philo);
	return (1);
}
