/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:50:55 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/07 08:06:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define MAX_INT 2147483647
#define MIN_INT_STR "-2147483648"

static t_bool	validate_handler(t_bool has_digit, char c, char *str);
static t_bool	is_bigger_than_int(const char *nptr);
static t_bool	check_int_limits(long result, int digit);

t_bool	validate_numbers(char *argv[])
{
	int		i;
	int		j;
	t_bool	has_digit;

	i = 1;
	while (argv[i])
	{
		j = 0;
		has_digit = false;
		if (argv[i][0] == '-')
			return (false);
		if (argv[i][0] == '+')
			j++;
		while (ft_isdigit(argv[i][j]))
		{
			if (ft_isdigit(argv[i][j]))
				has_digit = true;
			j++;
		}
		if (!validate_handler(has_digit, argv[i][j], argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	validate_handler(t_bool has_digit, char c, char *str)
{
	if (!has_digit || (c && !ft_isdigit(c)) || is_bigger_than_int(str))
		return (false);
	return (true);
}

static t_bool	is_bigger_than_int(const char *nptr)
{
	long	result;
	int		digit;

	result = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (ft_strcmp(MIN_INT_STR, nptr) == 0)
		return (false);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (true);
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if (check_int_limits(result, digit))
			return (true);
		result = result * 10 + *nptr++ - '0';
	}
	return (false);
}

static t_bool	check_int_limits(long result, int digit)
{
	if (result > MAX_INT / 10 || (result == MAX_INT / 10
			&& digit > MAX_INT % 10))
		return (true);
	return (false);
}
