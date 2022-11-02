/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/01 23:27:26 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	time_to_stop(t_table *table)
{
	t_philo	philo;
	int			i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		philo = table->philos[i];
		if (philo.table->times_a_philo_must_eat >= 0
			&& philo.times_eaten >= philo.table->times_a_philo_must_eat)
		{
			philo.table->stop++;
			return (1);
		}
	}
	return (0);
}

static int	time_to_die(t_table *table)
{
	t_philo	*philo;
	int			i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		philo = table->philos + i;
		if (current_time() - philo->last_meal > philo->table->time_to_die)
		{
			pthread_mutex_lock(table->die);
			print(philo, DEAD);
			pthread_mutex_unlock(table->die);
			return (1);
		}
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
