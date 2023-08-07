/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:12:58 by asekmani          #+#    #+#             */
/*   Updated: 2023/06/13 11:13:02 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_log(philo, 0, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_log(philo, 0, "has taken a fork");
	write_log(philo, 0, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	get_some_sleep(philo->table, philo->table->time_to_eat);
	if (stop_simulation(philo->table) == 0)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->nb_of_meal++;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (1);
}

static void	sleeping(t_philo *philo)
{
	write_log(philo, 0, "is sleeping");
	get_some_sleep(philo->table, philo->table->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	int	time_to_think;
	int	before_last_meal;

	before_last_meal = get_time() - philo->last_meal;
	time_to_think = (philo->table->time_to_die - before_last_meal
			- philo->table->time_to_eat) / 2;
	if (time_to_think <= 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	write_log(philo, 0, "is thinking");
	get_some_sleep(philo->table, time_to_think);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->table->nb_of_must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (philo->table->philo_nbr == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		get_some_sleep(philo->table, philo->table->time_to_eat);
	while (stop_simulation(philo->table) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
