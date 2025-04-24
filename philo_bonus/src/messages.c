/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/17 10:02:00 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

int	print_action(t_philo *philo, t_action action)
{
	static char	*actions[6] = {"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died", "debug"};

	if (philo->is_dead)
		return (0);
	sem_wait(philo->table->sem_print);
	printf("%lu %i %s\n", get_time(philo->table), philo->id + 1,
		actions[action]);
	if (action != die)
		sem_post(philo->table->sem_print);
	else
		philo->is_dead = 1;
	return (0);
}
