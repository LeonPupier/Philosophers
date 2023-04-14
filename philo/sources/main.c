/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:33:58 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/14 10:49:46 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Main functions of the program. Starts parsing,
 * error detection and program threads.
 * 
 * @param argc Number of program arguments supplied at runtime.
 * @param argv Array of character strings corresponding to the arguments passed.
 * @return (int) Returns the exit status of the program.
 * EXIT_SUCCESS in any case.
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (check_errors(argc, argv))
		return (EXIT_FAILURE);
	if (assign_data(&data, argc, argv))
		return (EXIT_FAILURE);
	init_all_mutex(&data);
	if (launch_threads(&data) == EXIT_SUCCESS)
	{
		loop_of_life(&data);
		declare_everyone_dead(&data);
		free_memory_and_mutex(&data);
		return (EXIT_SUCCESS);
	}
	free_memory_and_mutex(&data);
	return (EXIT_FAILURE);
}
