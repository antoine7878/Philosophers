/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/04 20:05:58 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

int	print_action(t_philo *philo, t_action action)
{
	static char	*actions[6] = {"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died", "debug"};

	pthread_mutex_lock(&philo->table->m_print);
	if (get_dead(philo->table) && action != die)
		return (pthread_mutex_unlock(&philo->table->m_print), -1);
	printf("%lu %i %s\n", get_time(philo->table), philo->id + 1,
		actions[action]);
	pthread_mutex_unlock(&philo->table->m_print);
	return (0);
}
