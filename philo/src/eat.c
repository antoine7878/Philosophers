/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:13 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/05 23:08:43 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <unistd.h>

static void	decrement_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_remaining_eat);
	if (philo->remaining_eat > 0)
		philo->remaining_eat--;
	pthread_mutex_unlock(&philo->m_remaining_eat);
}

int	get_remaining_meal(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->m_remaining_eat);
	ret = philo->remaining_eat;
	pthread_mutex_unlock(&philo->m_remaining_eat);
	return (ret);
}

long	get_last_eat(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->m_last_eat);
	ret = philo->last_eat;
	pthread_mutex_unlock(&philo->m_last_eat);
	return (ret);
}

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_eat);
	philo->last_eat = get_time(philo->table);
	pthread_mutex_unlock(&philo->m_last_eat);
}

int	ft_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (0);
	set_last_eat(philo);
	print_action(philo, eat);
	msleep(philo->table->eat_time, philo->table);
	release_forks(philo);
	decrement_meal(philo);
	print_action(philo, rest);
	msleep(philo->table->rest_time, philo->table);
	print_action(philo, think);
	msleep((philo->table->die_time - (get_time(philo->table)
				- get_last_eat(philo))) / 2, philo->table);
	return (0);
}
