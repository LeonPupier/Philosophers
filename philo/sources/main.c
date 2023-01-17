/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:33:58 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/17 13:05:12 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_data				data;
	int					count;

	if (check_errors(argc, argv))
		return (EXIT_FAILURE);
	if (assign_data(&data, argc, argv))
		return (EXIT_FAILURE);
	data.nb_forks = data.nb_of_philo - 1;
	gettimeofday(&data.init, NULL);
	count = -1;
	while (++count < data.nb_of_philo)
	{
		data.list_philo[count].data = &data;
		pthread_create(&data.list_philo[count].thread_id, NULL, \
		philosopher, (void *)&data.list_philo[count]);
	}
	while (1)
	{
	}
	free(data.list_philo);
	return (EXIT_SUCCESS);
}
