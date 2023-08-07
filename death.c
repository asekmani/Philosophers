/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:03:06 by asekmani          #+#    #+#             */
/*   Updated: 2023/06/13 11:03:14 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_table *table, int i)
{
	long	time;

	time = get_time();
	if ((time - table->philo[i]->last_meal) >= table->time_to_die)
	{
		write_log(table->philo[i], 1, "died");
		stop_flag(table, 1);
		pthread_mutex_unlock(&table->philo[i]->meal_time_lock);
		return (1);
	}
	return (0);
}

void	*check_philo_death(void *d)
{
	t_table	*table;

	table = (t_table *)d;
	stop_flag(table, 0);
	while (1)
	{
		if (must_eat_condition(table) == 1)
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}
