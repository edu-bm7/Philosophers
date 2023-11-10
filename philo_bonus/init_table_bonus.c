/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:41 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/10 09:44:02 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void		init_table_variables(t_table *table, int argc, char *argv[]);
static t_bool	init_forks_and_philos(t_table *table);

t_table	*init_table(int argc, char *argv[])
{
	t_table	*table;

	if (ft_atoi(argv[1]) == 0)
	{
		write(STDERR_FILENO, "Error: invalid arguments\n", 26);
		return (NULL);
	}
	table = malloc(sizeof(t_table));
	if (!table)
	{
		write(STDERR_FILENO, "Error: allocation failure\n", 26);
		return (NULL);
	}
	init_table_variables(table, argc, argv);
	table->pids = malloc(sizeof(pid_t) * table->philo_number);
	if (!table->pids)
	{
		free(table);
		return (NULL);
	}
	if (!init_forks_and_philos(table))
		return (NULL);
	return (table);
}

static t_bool	init_forks_and_philos(t_table *table)
{
	table->philos = init_philos(table->philo_number, table);
	if (!table->philos)
	{
		free(table);
		return (false);
	}
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT, 0644, table->philo_number);
	return (true);
}

static void	init_table_variables(t_table *table, int argc, char *argv[])
{
	table->philo_number = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = 0;
	table->starved = false;
	table->finish = false;
	sem_unlink("/starved");
	sem_unlink("/finish");
	sem_unlink("/block_print");
	table->starved_sem = sem_open("/starved", O_CREAT, 0644, 1);
	table->finish_sem = sem_open("/finish", O_CREAT, 0644, 1);
	table->block_print = sem_open("/block_print", O_CREAT, 0644, 1);
	if (argc == 6)
	{
		table->must_eat = ft_atoi(argv[5]);
		table->has_must_eat = true;
	}
	else
	{
		table->has_must_eat = false;
		table->must_eat = -1;
	}
}
