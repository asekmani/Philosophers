/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:33:20 by asekmani          #+#    #+#             */
/*   Updated: 2023/06/13 11:33:24 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philo[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->simulation_end);
}

void	*free_table(t_table *table)
{
	int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philo != NULL)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (table->philo[i] != NULL)
				free(table->philo[i]);
			i++;
		}
		free(table->philo);
	}
	free(table);
	return (NULL);
}
