/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbiter_routine_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:29 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:04 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	philos_finished(t_philo_node *current_philo, t_table *table);

void	*arbiter_routine(void *args)
{
	t_table			*table;
	t_philo_node	*current_philo;

	current_philo = (t_philo_node *)args;
	table = (t_table *)current_philo->table;
	while (true)
	{
		if (table->finish)
			return (NULL);
		if (philos_finished(current_philo, table))
			return (NULL);
		if (check_if_exit(table, current_philo))
			return (NULL);
		usleep(1000);
	}
}

static t_bool	philos_finished(t_philo_node *current_philo, t_table *table)
{
	if (table->has_must_eat)
	{
		sem_wait(table->finish_sem);
		if (current_philo->pass_must_eat)
		{
			table->finish = true;
			sem_post(table->finish_sem);
			return (true);
		}
		sem_post(table->finish_sem);
	}
	return (false);
}

t_bool	check_if_exit(t_table *table, t_philo_node *philo)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	sem_wait(table->finish_sem);
	if (timestamp - philo->last_meal > table->time_to_die)
	{
		table->starved = true;
		sem_post(table->finish_sem);
		unlock_forks(table);
		write_died_msg(timestamp, table, philo);
		return (true);
	}
	sem_post(table->finish_sem);
	return (false);
}
