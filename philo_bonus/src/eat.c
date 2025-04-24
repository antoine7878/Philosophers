/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:13 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/17 09:54:02 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_remaining_eat(t_philo *philo)
{
	int	ret;

	sem_wait(philo->sem_remaining_eat);
	ret = philo->remaining_eat;
	sem_post(philo->sem_remaining_eat);
	return (ret);
}

static void	decrement_remaining_eat(t_philo *philo)
{
	sem_wait(philo->sem_remaining_eat);
	philo->remaining_eat = philo->remaining_eat - 1;
	sem_post(philo->sem_remaining_eat);
}

long	get_last_eat(t_philo *philo)
{
	long	ret;

	sem_wait(philo->sem_last_eat);
	ret = philo->last_eat;
	sem_post(philo->sem_last_eat);
	return (ret);
}

void	set_last_eat(t_philo *philo)
{
	sem_wait(philo->sem_last_eat);
	philo->last_eat = get_time(philo->table);
	sem_post(philo->sem_last_eat);
}

int	ft_eat(t_philo *philo)
{
	sem_wait(philo->table->sem_forks);
	print_action(philo, take);
	if (philo->table->nb_philo > 1)
	{
		sem_wait(philo->table->sem_forks);
		print_action(philo, take);
		set_last_eat(philo);
		print_action(philo, eat);
		msleep(philo->eat_time, philo);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
		decrement_remaining_eat(philo);
		print_action(philo, rest);
		if (get_remaining_eat(philo) == 0)
			return (0);
		msleep(philo->rest_time, philo);
		print_action(philo, think);
		msleep((philo->table->die_time - (get_time(philo->table)
					- get_last_eat(philo))) / 2, philo);
	}
	else
		msleep((philo->table->die_time - (get_time(philo->table)
					- get_last_eat(philo))) / 2, philo);
	return (1);
}
