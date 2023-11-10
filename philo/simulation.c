/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:35:27 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:27 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table);

void	start_simulation(t_table *table)
{
	int				i;
	t_philo_node	*current;

	i = 1;
	current = table->philos->head;
	table->start_time = get_time_in_millis();
	while (i <= table->philo_number)
	{
		if (pthread_create(&current->thread, NULL,
				&philo_routine, (void *)current) != 0)
		{
			write(STDERR_FILENO, "Error: failed to create thread\n", 31);
			return ;
		}
		if (i == 1 && pthread_create(&table->arbiter, NULL,
				&arbiter_routine, (void *)table) != 0)
		{
			write(STDERR_FILENO, "Error: failed to create thread\n", 31);
			return ;
		}
		current = current->next;
		i++;
	}
	join_threads(table);
}

static void	join_threads(t_table *table)
{
	int				i;
	t_philo_node	*current;

	i = 1;
	current = table->philos->head;
	while (i <= table->philo_number)
	{
		if (pthread_join(current->thread, NULL) != 0)
		{
			write(STDERR_FILENO, "Error: failed to join threads\n", 30);
			return ;
		}
		if (i == 1 && pthread_join(table->arbiter, NULL) != 0)
		{
			write(STDERR_FILENO, "Error: failed to join threads\n", 30);
			return ;
		}
		i++;
		current = current->next;
	}
}
