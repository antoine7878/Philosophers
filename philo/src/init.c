/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:31:53 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/10 17:31:39 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static int	init_philos(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->m_print, NULL))
		return (printf("Error intializing print mutex\n"), -1);
	if (pthread_mutex_init(&table->m_dead, NULL))
		return (printf("Error intializing dead mutex\n"), -1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (-1);
	memset(table->philos, 0, sizeof(t_philo) * table->nb_philo);
	i = -1;
	while (++i < table->nb_philo)
	{
		table->philos[i].table = table;
		table->philos[i].id = i;
		table->philos[i].remaining_eat = table->nb_eat;
		if (pthread_mutex_init(&table->philos[i].m_fork, NULL))
			return (printf("Error intializing fork mutex\n"), -1);
		if (pthread_mutex_init(&table->philos[i].m_last_eat, NULL))
			return (printf("Error intializing last eat mutex\n"), -1);
		if (pthread_mutex_init(&table->philos[i].m_remaining_eat, NULL))
			return (printf("Error intializing remaining eat mutex\n"), -1);
		table->philos[i].next = &table->philos[(i + 1) % table->nb_philo];
	}
	return (0);
}

static void	*routine(void *philo_args)
{
	t_philo	*philo;

	philo = philo_args;
	print_action(philo, think);
	if (philo->table->nb_philo % 2 == 1)
	{
		if ((philo->id + 1) % 3 == 0)
			msleep((philo->table->eat_time * 2) * 0.9, philo->table);
		if ((philo->id + 2) % 3 == 0)
			msleep(philo->table->eat_time * 0.9, philo->table);
	}
	else
	{
		if ((philo->id + 1) % 2 == 0)
			msleep(philo->table->eat_time * 0.9, philo->table);
	}
	while (get_remaining_meal(philo) != 0 && !get_dead(philo->table))
	{
		if (ft_eat(philo) < 0)
			return (NULL);
	}
	return (NULL);
}

int	launch_philos(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time(table);
	while (i < table->nb_philo)
	{
		table->philos[i].last_eat = get_time(table);
		if (pthread_create(&table->philos[i].thread, NULL, routine,
				&table->philos[i]) < 0)
			return (printf("Error creating thread %i\n", i + 1), -1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (init_philos(table))
		return (-1);
	launch_philos(table);
	return (0);
}
