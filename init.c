/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:46:19 by asekmani          #+#    #+#             */
/*   Updated: 2023/05/27 14:46:33 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*forks_mutexes(t_table *table)
{
	pthread_mutex_t	*fork_locks;
	int				i;

	fork_locks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!fork_locks)
		return (NULL);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&fork_locks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (fork_locks);
}

int	mutexes_init(t_table *table)
{
	table->fork_locks = forks_mutexes(table);
	if (!table->fork_locks)
		return (0);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
	{
		if (table != NULL)
			free_table(table);
		return (0);
	}
	if (pthread_mutex_init(&table->simulation_end, 0) != 0)
	{
		if (table != NULL)
			free_table(table);
		return (0);
	}
	return (1);
}

void	ft_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		philo->fork[0] = philo->index;
		philo->fork[1] = (philo->index + 1) % philo->table->philo_nbr;
	}
	else
	{
		philo->fork[0] = (philo->index + 1) % philo->table->philo_nbr;
		philo->fork[1] = philo->index;
	}
}

void	**philo_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philo)
		return (NULL);
	while (i < table->philo_nbr)
	{
		table->philo[i] = malloc(sizeof(t_philo) * 1);
		if (!table->philo[i])
			return (NULL);
		table->philo[i]->table = table;
		if (pthread_mutex_init(&table->philo[i]->meal_time_lock, 0) != 0)
			return (NULL);
		table->philo[i]->index = i;
		table->philo[i]->nb_of_meal = 0;
		table->philo[i]->last_meal = get_time();
		ft_fork(table->philo[i]);
		i++;
	}
	return (NULL);
}

void	*table_init(t_table *table, int arc, char **arv)
{
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->end_of_simulation = 0;
	table->philo_nbr = ft_atoi(arv[1]);
	table->time_to_die = ft_atoi(arv[2]);
	table->time_to_eat = ft_atoi(arv[3]);
	table->time_to_sleep = ft_atoi(arv[4]);
	table->end_of_simulation = 0;
	table->nb_of_must_eat = -1;
	if (arc == 6)
		table->nb_of_must_eat = ft_atoi(arv[5]);
	philo_init(table);
	if (!philo_init(table))
		return (NULL);
	if (mutexes_init(table) == 0)
		return (NULL);
	return (table);
}
