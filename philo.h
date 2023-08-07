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

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	int					end_of_simulation;
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_must_eat;
	long				start_time;
	pthread_mutex_t		*fork_locks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		simulation_end;
	pthread_t			death;
	t_philo				**philo;
}						t_table;

typedef struct s_philo
{
	pthread_t			thr;
	t_table				*table;
	pthread_mutex_t		meal_time_lock;
	int					index;
	int					nb_of_meal;
	long				last_meal;
	int					fork[2];

}						t_philo;

long					get_time(void);
int						ft_atoi(const char *str);
int						mutexes_init(t_table *table);
int						death(t_table *table, int i);
int						start_simulation(t_table *table);
int						stop_simulation(t_table *table);
int						check_error(int arc, char **arv);
int						must_eat_condition(t_table *table);

void					get_some_sleep(t_table *table, int time_to);
void					stop_flag(t_table *table, int state);
void					ft_fork(t_philo *philo);
void					sim_start_delay(long start_time);
void					end_simulation(t_table *table);
void					**philo_init(t_table *table);
void					*table_init(t_table *table, int arc, char **arv);
void					write_log(t_philo *philo, int x, char *status);
void					*one_philo_case(t_philo *philo);
void					*philo_routine(void *ph);
void					*check_philo_death(void *d);
void					destroy_mutexes(t_table *table);
void					*free_table(t_table *table);
void					print_log(long time, int thread_index, char *status);

#endif
