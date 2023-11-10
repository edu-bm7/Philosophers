/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:46 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:01 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	exit_process(t_table *table, t_philo_node *current_philo);
static void	close_sem_and_free_resources(t_philo_node *current_philo,
				t_table *table);

void	*philo_routine(void *args)
{
	t_philo_node	*current_philo;
	t_table			*table;

	current_philo = (t_philo_node *)args;
	table = current_philo->table;
	while (true)
	{
		if (!take_forks(current_philo, table))
			break ;
		if (!eat(current_philo, table))
			break ;
		if (!sleeps(current_philo, table))
			break ;
		if (!think(current_philo, table))
			break ;
	}
	if (pthread_join(current_philo->arbiter, NULL) != 0)
	{
		sem_wait(current_philo->table->block_print);
		write(STDERR_FILENO, "Error: failed to join thread\n", 29);
		sem_post(current_philo->table->block_print);
		return (NULL);
	}
	exit_process(table, current_philo);
	return (NULL);
}

static void	close_sem_and_free_resources(t_philo_node *current_philo,
				t_table *table)
{
	sem_close(current_philo->table->block_print);
	sem_close(current_philo->table->forks);
	sem_close(current_philo->table->starved_sem);
	sem_close(current_philo->table->finish_sem);
	free_resources(table);
	free(table);
}

static void	exit_process(t_table *table, t_philo_node *current_philo)
{
	if (table->starved)
	{
		close_sem_and_free_resources(current_philo, table);
		exit(EXIT_FAILURE);
	}
	if (table->finish)
	{
		close_sem_and_free_resources(current_philo, table);
		exit(EXIT_SUCCESS);
	}
}
