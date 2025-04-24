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

void	set_dead(t_table *table)
{
	pthread_mutex_lock(&table->m_dead);
	table->dead = 1;
	pthread_mutex_unlock(&table->m_dead);
}

int	get_dead(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->m_dead);
	ret = table->dead;
	pthread_mutex_unlock(&table->m_dead);
	return (ret);
}

int	is_dead(t_philo *philo)
{
	if (get_remaining_meal(philo) == 0)
		return (0);
	if (get_time(philo->table) > get_last_eat(philo) + philo->table->die_time)
		return (1);
	return (0);
}

t_philo	*is_table_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (is_dead((&table->philos[i])))
			return (&table->philos[i]);
		i++;
	}
	return (NULL);
}
