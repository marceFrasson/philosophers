/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/09/21 19:48:34 by mfrasson         ###   ########.fr       */
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

typedef struct s_table	t_table;

typedef struct s_philosopher
{
    int             index;
    t_table         *table;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}               t_philosopher;

typedef struct s_table
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             times_a_philosopher_must_eat;
    long int        start;
    t_philosopher   *philosophers;
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