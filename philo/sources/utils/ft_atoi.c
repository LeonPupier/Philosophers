/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:28:43 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/10 10:24:13 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
 * @return (long) The result of the conversion.
 */
long	ft_atoi(const char *str)
{
	long long int	result;
	int				idx;
	int				sign;

	result = 0;
	idx = 0;
	sign = 1;
	if (!ft_strcmp(str, "-2147483648"))
		return (-2147483648);
	if (str[idx] == '+' || str[idx] == '-')
	{	
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] && str[idx] >= '0' && str[idx] <= '9')
	{
		if ((int)result != (((int)result * 10 + (str[idx] - 48)) / 10))
			return (ATOI_OVERFLOW);
		result = result * 10 + str[idx] - 48;
		idx++;
	}
	if (str[idx] || (str[idx - 1] < '0' || str[idx - 1] > '9'))
		return (ATOI_OVERFLOW);
	return ((long long)ft_conv(result * sign));
}

/**
 * @brief Comparison function between two character strings.
 * 
 * @param s1 String to compare.
 * @param s2 Character string to compare with [s1].
 * @return (int) Returns 0 if the two strings are identical,
 * the differences of their first character not common otherwise.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
