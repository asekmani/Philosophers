/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/06/13 13:32:03 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(long time, int thread_index, char *status)
{
	printf("%ld %d %s\n", time, thread_index, status);
}

void	write_log(t_philo *philo, int x, char *status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (stop_simulation(philo->table) == 1 && x == 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	print_log((get_time() - philo->table->start_time), philo->index + 1,
		status);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_log(philo, 0, "has taken a fork");
	get_some_sleep(philo->table, philo->table->time_to_die);
	write_log(philo, 0, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

int	main(int arc, char **arv)
{
	t_table	*table;

	table = NULL;
	if (arc < 5 || arc > 6)
	{
		printf("Eroor: Wrong number of arguments !!");
		exit(EXIT_FAILURE);
	}
	if (check_error(arc, arv) == 1)
		exit(EXIT_FAILURE);
	table = table_init(table, arc, arv);
	if (!table)
		return (EXIT_FAILURE);
	if (start_simulation(table) == 0)
		return (EXIT_FAILURE);
	end_simulation(table);
	return (EXIT_SUCCESS);
}
