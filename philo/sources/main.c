/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:33:58 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/11 15:55:29 by lpupier          ###   ########.fr       */
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
	launch_threads(&data);
	loop_of_life(&data);
	free_memory_and_mutex(&data);
	return (EXIT_SUCCESS);
}
