/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:43:56 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/10 10:45:02 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->next->m_fork);
	pthread_mutex_unlock(&philo->m_fork);
}

int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (print_action(philo, take) == 0)
		return (0);
	pthread_mutex_unlock(fork);
	return (-1);
}

int	take_forks(t_philo *philo)
{
	if (philo == philo->next)
		return (-1);
	if (philo->id == 0)
	{
		if (take_fork(philo, &philo->m_fork))
			return (-1);
		if (take_fork(philo, &philo->next->m_fork))
			return (pthread_mutex_unlock(&philo->m_fork), -1);
	}
	else
	{
		if (take_fork(philo, &philo->next->m_fork))
			return (-1);
		if (take_fork(philo, &philo->m_fork))
			return (pthread_mutex_unlock(&philo->next->m_fork), -1);
	}
	return (0);
}
