/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:31:53 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/17 10:31:51 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int	parse_argv(t_table *table, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	if (table->nb_philo <= 0)
		return (-1);
	table->die_time = ft_atoi(argv[2]);
	if (table->die_time < 0)
		return (-1);
	table->eat_time = ft_atoi(argv[3]);
	if (table->eat_time < 0)
		return (-1);
	table->rest_time = ft_atoi(argv[4]);
	if (table->rest_time < 0)
		return (-1);
	if (argv[5])
		table->nb_eat = ft_atoi(argv[5]);
	else
		table->nb_eat = -1;
	if (table->nb_eat < -1)
		return (-1);
	return (0);
}

int	init_sems(t_table *table, t_philo *philo)
{
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0600, table->nb_philo);
	if (!table->sem_forks)
		return (printf("Error forks semaphore creation\n"), 0);
	table->sem_print = sem_open(SEM_PRINT, O_CREAT, 0600, 1);
	if (!table->sem_print)
		return (printf("Error print semaphore creation\n"), 0);
	table->sem_dead = sem_open(SEM_DEAD, O_CREAT, 0600, 0);
	if (!table->sem_dead)
		return (printf("Error dead semaphore creation\n"), 0);
	philo->table = table;
	philo->rest_time = table->rest_time;
	philo->eat_time = table->eat_time;
	philo->remaining_eat = table->nb_eat;
	philo->sem_last_eat = sem_open(SEM_LAST_EAT, O_CREAT, 0600, 1);
	if (!philo->sem_last_eat)
		return (printf("Error last eat semaphore creation\n"), 0);
	philo->sem_remaining_eat = sem_open(SEM_REMAINING_EAT, O_CREAT, 0600, 1);
	if (!philo->sem_remaining_eat)
		return (printf("Error remaining eat semaphore creation\n"), 0);
	table->philo = philo;
	return (1);
}

void	*routine(t_table *table)
{
	table->philo->id = table->id;
	print_action(table->philo, think);
	set_last_eat(table->philo);
	if (table->philo->table->nb_philo % 2 == 1)
	{
		if ((table->philo->id + 1) % 3 == 0)
			msleep((table->philo->table->eat_time * 2) * 0.9, table->philo);
		if ((table->philo->id + 2) % 3 == 0)
			msleep(table->philo->table->eat_time * 0.9, table->philo);
	}
	else
	{
		if ((table->philo->id + 1) % 2 == 0)
			msleep(table->philo->table->eat_time * 0.9, table->philo);
	}
	while (get_remaining_eat(table->philo) != 0 && !is_dead(table->philo))
		ft_eat(table->philo);
	if (is_dead(table->philo))
		close_all(table, 1);
	close_all(table, 0);
	return (NULL);
}

int	launch_philos(t_table *table)
{
	table->pids = malloc(sizeof(pid_t) * table->nb_philo);
	if (!table->pids)
		return (0);
	table->start_time = get_time(table);
	while (table->id < table->nb_philo)
	{
		table->pids[table->id] = fork();
		if (table->pids[table->id] == -1)
			return (printf("Error creating fork\n"), -1);
		if (table->pids[table->id] == 0)
			routine(table);
		table->id++;
	}
	return (1);
}
