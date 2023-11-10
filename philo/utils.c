/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:35:30 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:31 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_millis(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_timestamp(long start_time)
{
	long	current_time;

	current_time = get_time_in_millis();
	return (current_time - start_time);
}

void	unlock_forks(t_fork_node *fork, t_table *table)
{
	pthread_mutex_unlock(&fork->left->mutex);
	if (table->philo_number != 1)
	{
		pthread_mutex_unlock(&fork->mutex);
	}
}

t_bool	check_if_finish_no_unlock(t_table *table)
{
	pthread_mutex_lock(&table->starved_mutex);
	if (table->starved || table->finish)
	{
		pthread_mutex_unlock(&table->starved_mutex);
		return (false);
	}
	pthread_mutex_unlock(&table->starved_mutex);
	return (true);
}

t_bool	check_if_finish(t_table *table, t_fork_node *fork)
{
	pthread_mutex_lock(&table->starved_mutex);
	if (table->starved || table->finish)
	{
		unlock_forks(fork, table);
		pthread_mutex_unlock(&table->starved_mutex);
		return (false);
	}
	pthread_mutex_unlock(&table->starved_mutex);
	return (true);
}
