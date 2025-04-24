/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:29:36 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/17 10:31:07 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_LAST_EAT "/sem_last_eat"
# define SEM_DEAD "/dead"
# define SEM_REMAINING_EAT "/remaining_eat"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef enum e_action	t_action;

typedef enum e_action
{
	take,
	eat,
	rest,
	think,
	die,
	debug
}						t_action;

typedef struct s_philo
{
	int					id;
	int					eat_time;
	int					rest_time;
	int					remaining_eat;
	long				last_eat;
	sem_t				*sem_last_eat;
	sem_t				*sem_remaining_eat;
	t_table				*table;
	int					is_dead;
}						t_philo;

typedef struct s_table
{
	int					nb_philo;
	int					die_time;
	int					eat_time;
	int					rest_time;
	int					nb_eat;
	int					id;
	long				start_time;
	pid_t				*pids;
	t_philo				*philo;
	struct timeval		tv;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	sem_t				*sem_dead;
}						t_table;

// init.c
int						parse_argv(t_table *table, char **argv);
int						init_sems(t_table *table, t_philo *philo);
int						launch_philos(t_table *table);

// ft_atoi.c
int						ft_atoi(char const *nptr);

// message.c
int						print_action(t_philo *philo, t_action action);

// eat.c
int						ft_eat(t_philo *philo);
void					set_last_eat(t_philo *philo);
long					get_last_eat(t_philo *philo);
int						get_remaining_eat(t_philo *philo);

// time.c
void					msleep(long msec, t_philo *philo);
long					get_time(t_table *table);

// death.c
int						is_dead(t_philo *philo);
void					close_all(t_table *table, int code);

#endif
