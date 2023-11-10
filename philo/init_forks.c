/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:35:08 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:09 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	push_forks(t_forks *forks, int index);
static void	init_new_fork_values(t_fork_node *new, int index);

t_forks	*init_forks(int nbr)
{
	t_forks	*forks;
	int		i;

	forks = malloc(sizeof(t_forks));
	if (!forks)
	{
		write(STDERR_FILENO, "Error: allocation failure\n", 26);
		return (NULL);
	}
	forks->head = NULL;
	forks->tail = NULL;
	i = 1;
	while (i <= nbr)
	{
		push_forks(forks, i);
		i++;
	}
	return (forks);
}

static void	push_forks(t_forks *forks, int index)
{
	t_fork_node	*new;
	t_fork_node	*current;

	new = malloc(sizeof(t_fork_node));
	if (!new)
	{
		write(STDERR_FILENO, "Error: allocation failure\n", 26);
		return ;
	}
	init_new_fork_values(new, index);
	if (!forks->head && !forks->tail)
	{
		new->right = new;
		new->left = new;
		forks->head = new;
		forks->tail = new;
		return ;
	}
	current = forks->tail;
	new->right = forks->head;
	new->left = current;
	current->right = new;
	forks->head->left = new;
	forks->tail = new;
}

static void	init_new_fork_values(t_fork_node *new, int index)
{
	new->index = index;
	pthread_mutex_init(&new->mutex, NULL);
	new->left = NULL;
	new->right = NULL;
}
