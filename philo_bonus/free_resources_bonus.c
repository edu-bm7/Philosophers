/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:32 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:04 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_resources(t_table *table)
{
	if (table->pids)
		free(table->pids);
	if (table->philos)
	{
		free_philos(table->philos, table->philo_number);
		free(table->philos);
	}
}

void	free_philos(t_philos *philos, int size)
{
	int				i;
	t_philo_node	*current;
	t_philo_node	*next;

	current = philos->head;
	i = 1;
	while (i <= size)
	{
		next = current->next;
		free(current);
		current = next;
		i++;
	}
	philos->head = NULL;
	philos->tail = NULL;
}
