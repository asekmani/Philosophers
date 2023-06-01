/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:45 by asekmani          #+#    #+#             */
/*   Updated: 2023/05/31 17:27:48 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	//
}

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time() + (table->philo_nbr * 2 * 10);
    //hello icic j'ai pas tres bien compris le principe !!!
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i]->thr, NULL,
				&philo_routine, table->philo[i]) != 0)
			return (0);
		i++;
	}
	if (table->philo_nbr > 1)
	{
		if (pthread_create(&table->death, NULL,
				&check_philo_death, table) != 0)
			return (0);
	}
	return (1);
}