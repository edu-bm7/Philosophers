/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:35:21 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:22 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo_node	*current_philo;
	t_fork_node		*current_fork;

	current_philo = (t_philo_node *)args;
	current_fork = current_philo->table->forks->head;
	while (current_fork)
	{
		if (current_fork->index == current_philo->index)
			break ;
		current_fork = current_fork->right;
	}
	if (current_philo->index % 2 == 0)
		usleep(1000);
	while (true)
	{
		if (!take_forks(current_fork, current_philo, current_philo->table))
			break ;
		if (!eat(current_fork, current_philo, current_philo->table))
			break ;
		if (!sleeps(current_philo, current_philo->table))
			break ;
		if (!think(current_philo, current_philo->table))
			break ;
	}
	return (NULL);
}
