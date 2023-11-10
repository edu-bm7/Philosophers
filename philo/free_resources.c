/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:34:59 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:34:59 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_table *table)
{
	if (table->forks)
	{
		free_forks(table->forks, table->philo_number);
		free(table->forks);
	}
	if (table->philos)
	{
		free_philos(table->philos, table->philo_number);
		free(table->philos);
	}
	pthread_mutex_destroy(&table->starved_mutex);
	pthread_mutex_destroy(&table->must_eat_mutex);
	free(table);
}

void	free_forks(t_forks *forks, int size)
{
	int			i;
	t_fork_node	*current;
	t_fork_node	*right;

	current = forks->head;
	i = 1;
	while (i <= size)
	{
		right = current->right;
		free(current);
		current = right;
		i++;
	}
	forks->head = NULL;
	forks->tail = NULL;
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
