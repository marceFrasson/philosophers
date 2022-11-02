/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/01 21:32:20 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>

# define FORK   0
# define EAT    1
# define SLEEP  2
# define THINK  3
# define DEAD   4

typedef struct s_table	t_table;

typedef struct s_philo
{
	int							index;
	t_table					*table;
	pthread_t				thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long int				last_meal;
	int							times_eaten;
}							t_philo;

typedef struct s_table
{
	int							number_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							times_a_philo_must_eat;
	int							deaths;
	long int				start;
	int							stop;
	t_philo					*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t *print;
	pthread_mutex_t *die;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*get;
	pthread_mutex_t	*set;
}							t_table;

/*
**  actions.c
*/

void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			drop_forks(t_philo *philo);
void			take_a_nap(t_philo *philo);
void			think(t_philo *philo);

/*
**  start_simulation.c
*/

void			init_mutexes(t_table *table);
void			create_philo(t_table *table);
int				start_simulation(t_table *table);

/*
**    end_simulation.c
*/

void			*continue_or_end(void *args);

/*
**    utils.c
*/

int				ft_atoi(const char *str);
long int	current_time(void);
void			sleep_ms(int time);
void			print(t_philo *philo, int action);

#endif
