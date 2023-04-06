/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:33:58 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/06 18:10:40 by lpupier          ###   ########.fr       */
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
	data.nb_forks = data.nb_of_philo;
	gettimeofday(&data.init, NULL);
	count = -1;
	while (++count < data.nb_of_philo)
	{
		data.list_philo[count].data = &data;
		pthread_create(&data.list_philo[count].thread_id, NULL, \
		philosopher, (void *)&data.list_philo[count]);
	}
	loop_of_life(&data);
	free(data.list_philo);
	return (EXIT_SUCCESS);
}

int	loop_of_life(t_data *data)
{
	int	running;

	running = 1;
	while (running)
	{
		(void)data;
	}
	return (1);
}
