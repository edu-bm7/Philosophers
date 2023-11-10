/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:38 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:03 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	push_philos(t_philos *philos, int index, t_table *table);
static void	init_new_philo_values(t_philo_node *new, int index, t_table *table);

t_philos	*init_philos(int nbr, t_table *table)
{
	t_philos	*philos;
	int			i;

	philos = malloc(sizeof(t_philos));
	if (!philos)
	{
		write(STDERR_FILENO, "Error: allocation failure\n", 26);
		return (NULL);
	}
	philos->head = NULL;
	philos->tail = NULL;
	i = 1;
	while (i <= nbr)
	{
		push_philos(philos, i, table);
		i++;
	}
	return (philos);
}

static void	push_philos(t_philos *philos, int index, t_table *table)
{
	t_philo_node	*new;
	t_philo_node	*current;

	new = malloc(sizeof(t_philo_node));
	if (!new)
	{
		write(STDERR_FILENO, "Error: allocation failure\n", 26);
		return ;
	}
	init_new_philo_values(new, index, table);
	if (!philos->head && !philos->tail)
	{
		new->next = new;
		new->prev = new;
		philos->head = new;
		philos->tail = new;
		return ;
	}
	current = philos->tail;
	new->next = philos->head;
	new->prev = current;
	current->next = new;
	philos->head->prev = new;
	philos->tail = new;
}

static void	init_new_philo_values(t_philo_node *new, int index, t_table *table)
{
	new->index = index;
	new->prev = NULL;
	new->next = NULL;
	new->table = table;
	new->last_meal = 0;
	new->ate = 0;
	new->pass_must_eat = false;
}
