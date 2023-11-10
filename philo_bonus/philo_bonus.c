/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:36:39 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/07 08:06:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_semaphores(t_table *table);

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
	unlink_semaphores(table);
	free(table);
	return (0);
}

void	unlink_semaphores(t_table *table)
{
	sem_close(table->starved_sem);
	sem_close(table->finish_sem);
	sem_close(table->forks);
	sem_close(table->block_print);
	sem_unlink("/block_print");
	sem_unlink("/forks");
	sem_unlink("/starved");
	sem_unlink("/finish");
}
