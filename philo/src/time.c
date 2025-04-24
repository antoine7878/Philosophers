/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 22:24:05 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/05 22:24:24 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <bits/types/struct_timeval.h>
#include <unistd.h>

long	get_cur_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(long msec, t_table *table)
{
	long	start;

	start = get_cur_time();
	while (get_cur_time() < start + msec && !get_dead(table))
		usleep(100);
}

long	get_time(t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - table->start_time);
}
