/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:51 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:43:59 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	unlock_forks(t_table *table)
{
	sem_post(table->forks);
	sem_post(table->forks);
}

t_bool	check_if_finish_no_unlock(t_table *table)
{
	sem_wait(table->finish_sem);
	if (table->finish || table->starved)
	{
		sem_post(table->finish_sem);
		return (false);
	}
	sem_post(table->finish_sem);
	return (true);
}

t_bool	check_if_finish(t_table *table)
{
	sem_wait(table->finish_sem);
	if (table->finish || table->starved)
	{
		unlock_forks(table);
		sem_post(table->finish_sem);
		return (false);
	}
	sem_post(table->finish_sem);
	return (true);
}
