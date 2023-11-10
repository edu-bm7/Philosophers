/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:55:57 by ebezerra          #+#    #+#             */
/*   Updated: 2023/11/09 03:38:39 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_table	t_table;

typedef struct s_philo_node {
	int					index;
	pthread_t			arbiter;
	long				last_meal;
	int					ate;
	t_bool				pass_must_eat;
	t_table				*table;
	struct s_philo_node	*next;
	struct s_philo_node	*prev;
}	t_philo_node;

typedef struct s_philos {
	t_philo_node		*head;
	t_philo_node		*tail;
}	t_philos;

typedef struct s_table {
	t_philos			*philos;
	pid_t				*pids;
	sem_t				*starved_sem;
	sem_t				*finish_sem;
	sem_t				*block_print;
	sem_t				*forks;
	t_bool				starved;
	t_bool				finish;
	t_bool				has_must_eat;
	long				start_time;
	int					philo_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
}	t_table;

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
int			ft_isxdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
t_bool		validate_numbers(char *argv[]);
long		get_time_in_millis(void);
long		get_timestamp(long start_time);
void		start_simulation(t_table *table);
void		free_philos(t_philos *philos, int size);
void		*philo_routine(void *args);
t_bool		take_forks(t_philo_node *philo, t_table *table);
t_bool		eat(t_philo_node *philo, t_table *table);
t_bool		sleeps(t_philo_node *philo, t_table *table);
t_bool		think(t_philo_node *philo, t_table *table);
void		*arbiter_routine(void *args);
t_table		*init_table(int argc, char *argv[]);
t_philos	*init_philos(int nbr, t_table *table);
void		free_resources(t_table *table);
void		unlock_forks(t_table *table);
t_bool		check_if_exit(t_table *table, t_philo_node *philo);
void		write_eat_msg(long timestamp, t_table *table, t_philo_node *philo);
void		write_sleep_msg(long timestamp, t_table *table,
				t_philo_node *philo);
void		write_think_msg(long timestamp, t_table *table,
				t_philo_node *philo);
void		write_fork_msg(long timestamp, t_table *table, t_philo_node *philo);
void		write_died_msg(long timestamp, t_table *table, t_philo_node *philo);
t_bool		check_if_finish(t_table *table);
t_bool		check_if_finish_no_unlock(t_table *table);
t_bool		pass_must_eat(t_table *table, t_philo_node *philo);

#endif
