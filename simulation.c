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
}

void	get_some_sleep(t_table *table, int time_to)
{
	long	wake_up;

	wake_up = get_time() + time_to;
	while (get_time() < wake_up)
	{
		if (stop_simulation(table))
			break ;
		usleep(100);
	}
		
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

static int	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	//print_log(get_time(), philo->index, "has taken a fork");
	write_log(philo, 0, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	//print_log(get_time(), philo->index, "has taken a fork");
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
	//time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep;
	int before_last_meal = get_time() - philo->last_meal;
	time_to_think = (philo->table->time_to_die - before_last_meal 
	- philo->table->time_to_eat ) / 2;
	if(time_to_think <= 0 )
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	write_log(philo, 0, "is thinking");
	get_some_sleep(philo->table, time_to_think);
	
}

static void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_log(philo, 0, "has taken a fork");
	get_some_sleep(philo->table, philo->table->time_to_die);
	write_log(philo, 0, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

static void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->table->philo_nbr == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	if(philo->index % 2 == 0)
	{
		get_some_sleep(philo->table, philo->table->time_to_eat);
	}
	while (stop_simulation(philo->table) == 0)
	{	
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	stop_flag(t_table *table, int state)
{
	pthread_mutex_lock(&table->simulation_end);
		table->end_of_simulation = state;
	pthread_mutex_unlock(&table->simulation_end);
}

int		death(t_table	*table, int i)
{
	long	time;

	time = get_time();
	if ((time - table->philo[i]->last_meal) >= table->time_to_die)
	{
		stop_flag(table, 1);
		write_log(table->philo[i], 1, "died");
		pthread_mutex_unlock(&table->philo[i]->meal_time_lock);
		return (1);
	}
	return (0);
}

void	*check_philo_death(void *d)
{
	t_table			*table;

	table = (t_table *)d;
	stop_flag(table, 0);
	while (1)
	{
			if(must_eat_condition(table) == 1)
				return (NULL);
		usleep(100);
	}
	return (NULL);
}


int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
    //hello ici j'ai pas tres bien compris le principe !!!
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