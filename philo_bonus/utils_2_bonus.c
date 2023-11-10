/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:56:35 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:56:36 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	pass_must_eat(t_table *table, t_philo_node *philo)
{
	sem_wait(table->finish_sem);
	philo->pass_must_eat = true;
	sem_post(table->finish_sem);
	unlock_forks(table);
	return (false);
}
