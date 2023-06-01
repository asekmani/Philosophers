/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:04:14 by asekmani          #+#    #+#             */
/*   Updated: 2023/03/29 11:04:30 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	int				end_of_simulation;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_must_eat;
	long			start_time;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	simulation_end;
	pthread_t		death;
	t_philo			**philo;
}			t_table;

typedef struct s_philo
{
	pthread_t			thr;
	t_table				*table;
	pthread_mutex_t		meal_time_lock;
	int					index;
	int					nb_of_meal;
	long				last_meal;
	int					fork[2];
	
}			t_philo;


int		ft_atoi(const char *str);
int     check_error(int arc, char **arv);

#endif
