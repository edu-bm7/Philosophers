/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:26 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:06 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	take_forks(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	if (table->philo_number != 1)
	{
		sem_wait(table->forks);
		sem_wait(table->forks);
	}
	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish(table))
		return (false);
	write_fork_msg(timestamp, table, philo);
	if (table->philo_number == 1)
		usleep((table->time_to_die * 1000) + 2000);
	if (!check_if_finish(table))
		return (false);
	timestamp = get_timestamp(table->start_time);
	write_fork_msg(timestamp, table, philo);
	if (!check_if_finish(table))
		return (false);
	return (true);
}

t_bool	eat(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish(table))
		return (false);
	write_eat_msg(timestamp, table, philo);
	if (!check_if_finish(table))
		return (false);
	sem_wait(table->finish_sem);
	philo->last_meal = timestamp;
	sem_post(table->finish_sem);
	if (table->has_must_eat)
	{
		philo->ate++;
		if (philo->ate >= table->must_eat)
			return (pass_must_eat(table, philo));
	}
	usleep(table->time_to_eat * 1000);
	if (!check_if_finish(table))
		return (false);
	unlock_forks(table);
	return (true);
}

t_bool	sleeps(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish_no_unlock(table))
		return (false);
	write_sleep_msg(timestamp, table, philo);
	if (!check_if_finish_no_unlock(table))
		return (false);
	usleep(table->time_to_sleep * 1000);
	if (!check_if_finish_no_unlock(table))
		return (false);
	return (true);
}

t_bool	think(t_philo_node *philo, t_table *table)
{
	long	timestamp;

	if (!check_if_finish_no_unlock(table))
		return (false);
	timestamp = get_timestamp(table->start_time);
	if (!check_if_finish_no_unlock(table))
		return (false);
	write_think_msg(timestamp, table, philo);
	if (!check_if_finish_no_unlock(table))
		return (false);
	return (true);
}
