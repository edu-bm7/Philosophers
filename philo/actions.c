/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:34:50 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:34:52 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	take_forks(t_fork_node *fork, t_philo_node *philo, t_table *table)
{
	long	timestamp;

	if (table->philo_number != 1)
		get_forks(table, philo, fork);
	else
		pthread_mutex_lock(&fork->mutex);
	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish(table, fork))
		return (false);
	write_fork_msg(timestamp, table, philo);
	if (table->philo_number == 1)
		usleep((table->time_to_die * 1000) + 2000);
	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish(table, fork))
		return (false);
	write_fork_msg(timestamp, table, philo);
	return (true);
}

t_bool	eat(t_fork_node *fork, t_philo_node *philo, t_table *table)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish(table, fork))
		return (false);
	write_eat_msg(timestamp, table, philo);
	pthread_mutex_lock(&table->starved_mutex);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(&table->starved_mutex);
	if (table->has_must_eat)
	{
		philo->ate++;
		if (philo->ate >= table->must_eat)
			return (passed_must_eat(table, philo, fork));
	}
	usleep(table->time_to_eat * 1000);
	if (!check_if_finish(table, fork))
		return (false);
	unlock_forks(fork, table);
	return (true);
}

t_bool	sleeps(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish_no_unlock(table))
		return (false);
	write_sleep_msg(timestamp, table, philo);
	usleep(table->time_to_sleep * 1000);
	if (!check_if_finish_no_unlock(table))
		return (false);
	return (true);
}

t_bool	think(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish_no_unlock(table))
		return (false);
	write_think_msg(timestamp, table, philo);
	if (!check_if_finish_no_unlock(table))
		return (false);
	return (true);
}
