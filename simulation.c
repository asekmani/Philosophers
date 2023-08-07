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

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i]->thr, NULL, &philo_routine,
				table->philo[i]) != 0)
		{
			if (table != NULL)
				free_table(table);
			return (0);
		}
		i++;
	}
	if (table->philo_nbr > 1)
	{
		if (pthread_create(&table->death, NULL, &check_philo_death, table) != 0)
		{
			if (table != NULL)
				free_table(table);
			return (0);
		}
	}
	return (1);
}

int	stop_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->simulation_end);
	if (table->end_of_simulation == 1)
		i = 1;
	pthread_mutex_unlock(&table->simulation_end);
	return (i);
}

void	end_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i]->thr, NULL);
		i++;
	}
	if (table->philo_nbr > 1)
		pthread_join(table->death, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	must_eat_condition(t_table *table)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philo[i]->meal_time_lock);
		if (death(table, i))
			return (1);
		if (table->nb_of_must_eat != -1)
			if (table->philo[i]->nb_of_meal < table->nb_of_must_eat)
				count = 0;
		pthread_mutex_unlock(&table->philo[i]->meal_time_lock);
		i++;
	}
	if (table->nb_of_must_eat != -1 && count == 1)
	{
		stop_flag(table, 1);
		return (1);
	}
	return (0);
}
