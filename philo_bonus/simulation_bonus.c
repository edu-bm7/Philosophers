/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:49 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:00 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void		wait_for_process(pid_t *pids, t_table *table);
static t_bool	waitpid_routine(pid_t *pids, int i, int *k, t_table *table);
static void		kill_process(t_table *table, pid_t *pids, int i);
static void		wait_for_process_handler(t_table *table);

void	start_simulation(t_table *table)
{
	int				i;
	t_philo_node	*current;

	i = 0;
	current = table->philos->head;
	table->start_time = get_time_in_millis();
	while (i < table->philo_number)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
		{
			if (pthread_create(&current->arbiter, NULL,
					&arbiter_routine, (void *)current) != 0)
			{
				sem_wait(table->block_print);
				write(STDERR_FILENO, "Error: failed to create thread\n", 31);
				sem_post(table->block_print);
			}
			philo_routine((void *)current);
			break ;
		}
		i++;
		current = current->next;
	}
	wait_for_process_handler(table);
}

static void	wait_for_process_handler(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (table->pids[i] != 0)
		{
			wait_for_process(table->pids, table);
			break ;
		}
	}
}

static void	wait_for_process(pid_t *pids, t_table *table)
{
	int		i;
	int		k;

	k = 0;
	while (true)
	{
		i = 0;
		while (i < table->philo_number)
		{
			if (k == table->philo_number)
				return ;
			if (pids[i] > 0)
			{
				if (!waitpid_routine(pids, i, &k, table))
					return ;
			}
			i++;
		}
	}
}

t_bool	waitpid_routine(pid_t *pids, int i, int *k, t_table *table)
{
	pid_t	result;
	int		status;

	result = waitpid(pids[i], &status, WNOHANG);
	if (result > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_process(table, pids, i);
				return (false);
			}
			else if (WEXITSTATUS(status) == 0)
			{
				pids[i] = -1;
				(*k)++;
			}
		}
	}
	else if (result == -1)
		return (false);
	return (true);
}

static void	kill_process(t_table *table, pid_t *pids, int i)
{
	int	j;

	j = 0;
	while (j < table->philo_number)
	{
		if (j != i)
			kill(pids[j], SIGKILL);
		j++;
	}
}
