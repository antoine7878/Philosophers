/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:03:59 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/17 10:30:44 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	sem_unlink_all(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LAST_EAT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_REMAINING_EAT);
}

void	ft_sem_close(sem_t **sem)
{
	if (*sem)
		sem_close(*sem);
	*sem = NULL;
}

void	close_all(t_table *table, int code)
{
	free(table->pids);
	ft_sem_close(&table->philo->sem_last_eat);
	ft_sem_close(&table->philo->sem_remaining_eat);
	ft_sem_close(&table->sem_dead);
	ft_sem_close(&table->sem_print);
	ft_sem_close(&table->sem_forks);
	sem_unlink_all();
	exit(code);
}

void	end_prog(t_table *table, int count)
{
	int		i;
	int		status;

	i = 0;
	if (count >= table->nb_philo)
		return ;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) > 0)
	{
		while (i < table->nb_philo)
		{
			kill(table->pids[i++], SIGKILL);
		}
	}
	else
		end_prog(table, count + 1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	philo;

	sem_unlink_all();
	memset(&philo, 0, sizeof(t_philo));
	memset(&table, 0, sizeof(t_table));
	table.philo = &philo;
	philo.table = &table;
	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments\n"), 1);
	if (parse_argv(&table, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (init_sems(&table, &philo) && launch_philos(&table))
		end_prog(&table, 0);
	close_all(&table, 0);
	return (0);
}
