/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbiter_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:34:55 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:34:56 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*print_dead_philo_msg(t_table *table, t_philo_node *philo,
					long timestamp);
static t_bool	philos_finished(t_table *table);
static t_bool	check_if_dead(long timestamp, t_philo_node *current_philo,
					t_table *table);

void	*arbiter_routine(void *args)
{
	t_table			*table;
	long			timestamp;
	t_philo_node	*current_philo;
	int				i;

	table = (t_table *)args;
	current_philo = table->philos->head;
	while (true)
	{
		i = 1;
		if (table->finish || table->starved)
			return (NULL);
		while (i <= table->philo_number)
		{
			if (philos_finished(table))
				return (NULL);
			timestamp = get_timestamp(table->start_time);
			if (!check_if_dead(timestamp, current_philo, table))
				return (NULL);
			current_philo = current_philo->next;
			i++;
		}
		usleep(1000);
	}
}

static t_bool	check_if_dead(long timestamp, t_philo_node *current_philo,
					t_table *table)
{
	pthread_mutex_lock(&table->starved_mutex);
	if (timestamp - current_philo->last_meal > table->time_to_die)
	{
		pthread_mutex_unlock(&table->starved_mutex);
		return (print_dead_philo_msg(table, current_philo, timestamp) != NULL);
	}
	pthread_mutex_unlock(&table->starved_mutex);
	return (true);
}

static void	*print_dead_philo_msg(t_table *table, t_philo_node *philo,
				long timestamp)
{
	int			i;
	t_fork_node	*current;

	i = 0;
	pthread_mutex_lock(&table->starved_mutex);
	table->starved = true;
	write_died_msg(timestamp, table, philo);
	current = table->forks->head;
	while (i < table->philo_number)
	{
		if (current->index == philo->index)
			break ;
		current = current->right;
		i++;
	}
	pthread_mutex_unlock(&table->starved_mutex);
	return (NULL);
}

static t_bool	finish_philosopher(t_table *table)
{
	pthread_mutex_lock(&table->starved_mutex);
	table->finish = true;
	pthread_mutex_unlock(&table->starved_mutex);
	return (true);
}

static t_bool	philos_finished(t_table *table)
{
	int				i;
	int				finished_count;
	t_philo_node	*current_philo;

	i = 1;
	finished_count = 0;
	current_philo = table->philos->head;
	if (table->has_must_eat)
	{
		while (i <= table->philo_number)
		{
			pthread_mutex_lock(&table->must_eat_mutex);
			if (current_philo->pass_must_eat)
				finished_count++;
			pthread_mutex_unlock(&table->must_eat_mutex);
			i++;
			current_philo = current_philo->next;
		}
		if (finished_count == table->philo_number)
			return (finish_philosopher(table));
	}
	return (false);
}
