/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:29:36 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/10 17:53:13 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

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
	char				dead;
	int					remaining_eat;
	long				last_eat;
	int					think_time;
	int					initial_think_time;

	pthread_t			thread;

	pthread_mutex_t		m_fork;
	pthread_mutex_t		m_last_eat;
	pthread_mutex_t		m_remaining_eat;

	t_table				*table;
	t_philo				*next;
}						t_philo;

typedef struct s_table
{
	struct timeval		tv;

	long				start_time;

	int					nb_philo;
	int					die_time;
	int					eat_time;
	int					rest_time;
	int					nb_eat;
	int					dead;
	int					go;

	t_philo				*philos;

	pthread_mutex_t		m_print;
	pthread_mutex_t		m_dead;
}						t_table;

// init.c
int						parse_argv(t_table *table, char **argv);
int						init_table(t_table *table);
int						launch_philos(t_table *table);

// ft_atoi.c
int						ft_atoi(char const *nptr);

// message.c
int						print_action(t_philo *philo, t_action action);

// eat.c
int						ft_eat(t_philo *philo);
void					set_last_eat(t_philo *philo);
long					get_last_eat(t_philo *philo);
int						get_remaining_meal(t_philo *philo);

// time.c
void					msleep(long msec, t_table *table);
long					get_time(t_table *table);
int						get_dead(t_table *table);

// death.c
void					set_dead(t_table *table);
int						get_dead(t_table *table);
int						is_dead(t_philo *philo);
t_philo					*is_table_dead(t_table *table);

// forks.c
void					release_forks(t_philo *philo);
int						take_forks(t_philo *philo);

#endif
