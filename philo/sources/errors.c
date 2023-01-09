/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:38:36 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/06 16:06:38 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	check_errors(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
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
