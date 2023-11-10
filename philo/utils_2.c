/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:58:26 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:58:27 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_table *table, t_philo_node *philo, t_fork_node *fork)
{
	if (philo->index == table->philo_number)
	{
		pthread_mutex_lock(&fork->mutex);
		pthread_mutex_lock(&fork->left->mutex);
	}
	else
	{
		pthread_mutex_lock(&fork->left->mutex);
		pthread_mutex_lock(&fork->mutex);
	}
}

t_bool	passed_must_eat(t_table *table, t_philo_node *philo, t_fork_node *fork)
{
	pthread_mutex_lock(&table->must_eat_mutex);
	philo->pass_must_eat = true;
	pthread_mutex_unlock(&table->must_eat_mutex);
	unlock_forks(fork, table);
	return (false);
}
