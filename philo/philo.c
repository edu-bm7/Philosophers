/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:36:39 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/06 04:33:50 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "Error: invalid number of arguments\n", 35);
		return (EXIT_FAILURE);
	}
	if (!validate_numbers(argv))
	{
		write(STDERR_FILENO, "Error: invalid arguments\n", 25);
		return (EXIT_FAILURE);
	}
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	start_simulation(table);
	free_resources(table);
	return (0);
}
