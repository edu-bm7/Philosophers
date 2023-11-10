/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_msgs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:56 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:43:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_eat_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	sem_wait(table->block_print);
	printf("%ldms %i is eating\n", timestamp, philo->index);
	sem_post(table->block_print);
}

void	write_sleep_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	sem_wait(table->block_print);
	printf("%ldms %i is sleeping\n", timestamp, philo->index);
	sem_post(table->block_print);
}

void	write_think_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	sem_wait(table->block_print);
	printf("%ldms %i is thinking\n", timestamp, philo->index);
	sem_post(table->block_print);
}

void	write_fork_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	sem_wait(table->block_print);
	printf("%ldms %i has taken a fork\n", timestamp, philo->index);
	sem_post(table->block_print);
}

void	write_died_msg(long timestamp, t_table *table, t_philo_node *philo)
{
	sem_wait(table->block_print);
	printf("%ldms %i died\n", timestamp, philo->index);
	sem_post(table->block_print);
}
