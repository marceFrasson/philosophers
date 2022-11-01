/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/09/28 14:53:21 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

# define false  0
# define true   1

# define END    1

# define FORK   0
# define EAT    1
# define SLEEP  2
# define THINK  3
# define DEAD   4

typedef struct s_table	t_table;

typedef struct s_philo
{
    int             index;
    t_table         *table;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long int        last_meal;
    int             times_eaten;
}               t_philo;

typedef struct s_table
{
    int             number_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             times_a_philo_must_eat;
    int             deaths;
    long int        start;
    int             stop;
    t_philo         *philos;
    pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}               t_table;

/*
**    utils.c
*/

int	ft_atoi(const char *str);

/*
**    philosophers.c
*/



#endif