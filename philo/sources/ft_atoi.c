/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:28:43 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/12 08:44:31 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	ft_check_overflow(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

static long long int	ft_conv(long long int res)
{
	if (res > INT_MAX)
		return (res - LLONG_MAX - 1);
	else if (res < INT_MIN)
		return (res - LLONG_MIN);
	else
		return (res);
}

/**
 * @brief This function is used to transform a character string, representing
 * an integer value, into a numeric value of type int. The term atoi is an
 * acronym meaning: ASCII to integer.
 * 
 * @param str The character string to convert.
 * @return (int) The result of the conversion.
 */
int	ft_atoi(const char *str)
{
	long long int	result;
	int				idx;
	int				sign;

	result = 0;
	idx = 0;
	sign = 1;
	while (str[idx] == ' ' || (str[idx] >= 9 && str[idx] <= 13))
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{	
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] && str[idx] >= '0' && str[idx] <= '9')
	{
		if (result != ((result * 10 + (str[idx] - 48)) / 10))
			return (ft_check_overflow(sign));
		result = result * 10 + str[idx] - 48;
		idx++;
	}
	return ((int)ft_conv(result * sign));
}
