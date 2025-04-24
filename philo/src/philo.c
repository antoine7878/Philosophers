/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:03:59 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/05 23:09:48 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	wait_end(t_table *table)
{
	int	i;
	int	j;

	while (1)
	{
		j = 0;
		i = 0;
		while (i < table->nb_philo)
		{
			if (is_dead((&table->philos[i])))
			{
				set_dead(table);
				print_action(&table->philos[i], die);
				return ;
			}
			if (get_remaining_meal(&table->philos[i]) == 0)
				j++;
			i++;
			usleep(500);
		}
		if (j == table->nb_philo)
			return ;
	}
	i = 0;
}

static void	close_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philos[i++].thread, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i].m_last_eat);
		pthread_mutex_destroy(&table->philos[i].m_remaining_eat);
		pthread_mutex_destroy(&table->philos[i].m_fork);
		i++;
	}
	free(table->philos);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_dead);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments\n"), 1);
	memset(&table, 0, sizeof(t_table));
	if (parse_argv(&table, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (init_table(&table) == 0)
		wait_end(&table);
	close_all(&table);
	return (0);
}
