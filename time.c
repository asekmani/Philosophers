/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:03:58 by asekmani          #+#    #+#             */
/*   Updated: 2023/06/13 11:04:02 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	get_some_sleep(t_table *table, int time_to)
{
	long	wake_up;

	wake_up = get_time() + time_to;
	while (get_time() < wake_up)
	{
		if (stop_simulation(table))
			break ;
		usleep(500);
	}
}

void	sim_start_delay(long start_time)
{
	while (get_time() < start_time)
		continue ;
}

void	stop_flag(t_table *table, int state)
{
	pthread_mutex_lock(&table->simulation_end);
	table->end_of_simulation = state;
	pthread_mutex_unlock(&table->simulation_end);
}
