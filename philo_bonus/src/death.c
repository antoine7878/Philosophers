/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:37:27 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/05 23:09:02 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo)
{
	if (get_remaining_eat(philo) == 0)
		return (0);
	if (get_time(philo->table) > get_last_eat(philo) + philo->table->die_time)
	{
		print_action(philo, die);
		return (1);
	}
	return (0);
}
