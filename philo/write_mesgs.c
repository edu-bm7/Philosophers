/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:35:36 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:36 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_eat_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	pthread_mutex_lock(&table->block_print);
	printf("%ldms %i is eating\n", timestamp, philo->index);
	pthread_mutex_unlock(&table->block_print);
}

void	write_think_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	pthread_mutex_lock(&table->block_print);
	printf("%ldms %i is thinking\n", timestamp, philo->index);
	pthread_mutex_unlock(&table->block_print);
}

void	write_sleep_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	pthread_mutex_lock(&table->block_print);
	printf("%ldms %i is sleeping\n", timestamp, philo->index);
	pthread_mutex_unlock(&table->block_print);
}

void	write_fork_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	pthread_mutex_lock(&table->block_print);
	printf("%ldms %i has taken a fork\n", timestamp, philo->index);
	pthread_mutex_unlock(&table->block_print);
}

void	write_died_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	pthread_mutex_lock(&table->block_print);
	printf("%ldms %i died\n", timestamp, philo->index);
	pthread_mutex_unlock(&table->block_print);
}
