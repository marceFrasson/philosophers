/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/04 01:46:48 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	time_to_stop(t_table *table)
{
	int			i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		pthread_mutex_lock(table->eating);
		if (table->times_a_philo_must_eat >= 0
			&& (table->philos + i)->times_eaten
			>= table->times_a_philo_must_eat)
		{
			table->stop++;
			pthread_mutex_unlock(table->eating);
			return (1);
		}
		pthread_mutex_unlock(table->eating);
	}
	return (0);
}

static int	time_to_die(t_table *table)
{
	int			i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		pthread_mutex_lock(table->eating);
		if (!(table->philos + i)->last_meal)
			(table->philos + i)->last_meal = table->start;
		if (current_time() - (table->philos + i)->last_meal
			> table->time_to_die)
		{
			print(table->philos + i, DEAD);
			pthread_mutex_unlock(table->eating);
			return (1);
		}
		pthread_mutex_unlock(table->eating);
	}
	return (0);
}

void	*continue_or_end(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	while (true)
	{
		sleep_ms(1);
		if (time_to_die(table))
			break ;
		if (time_to_stop(table))
			break ;
	}
	return (NULL);
}
