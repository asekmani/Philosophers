/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/05/24 12:11:28 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(long time, int thread_index, char  *status)
{
	printf("%ld %d %s\n",time, thread_index, status);
}

void	write_log(t_philo *philo, int x, char *status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (stop_simulation(philo->table) == 1 && x == 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	print_log((get_time() - philo->table->start_time), philo->index, status);
	pthread_mutex_unlock(&philo->table->write_lock);
}

static void sim_stop(t_table *table)
{
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    pthread_join(table->philo[i]->thr, NULL);
    i++;
  }
}

int main(int arc, char **arv)
{
  t_table *table;

    table = NULL;
    if(arc < 5 || arc > 6)
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
    sim_stop(table);
}