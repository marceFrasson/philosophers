/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/04 01:53:36 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		pthread_mutex_init(table->forks + i, NULL);
	pthread_mutex_init(table->printing, NULL);
	pthread_mutex_init(table->eating, NULL);
}

void	create_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		philo = table->philos + i;
		philo->index = i + 1;
		philo->table = table;
		philo->left_fork = table->forks + i;
		philo->right_fork = table->forks + i + 1;
		philo->times_eaten = 0;
	}
	philo->right_fork = table->forks;
}

void	one_philo(t_philo *philo)
{
	print(philo, FORK);
	print(philo, DEAD);
}

static void	*simulation(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->table->number_of_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->index % 2)
		sleep_ms(2);
	while (true)
	{
		if (philo->table->deaths || philo->table->stop)
			break ;
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (philo->times_eaten == philo->table->times_a_philo_must_eat)
			break ;
		take_a_nap(philo);
		think(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	end_thread;
	int			i;

	i = -1;
	table->start = current_time();
	while (++i < table->number_of_philos)
		if (pthread_create(&(table->philos + i)->thread, NULL, &simulation,
				table->philos + i))
			return (1);
	if (pthread_create(&end_thread, NULL, &continue_or_end, table))
		return (1);
	i = -1;
	while (++i < table->number_of_philos)
		if (pthread_join((table->philos + i)->thread, NULL))
			return (1);
	if (pthread_join(end_thread, NULL))
		return (1);
	if (!table->deaths)
		printf("\nall philosophers with full tummy\n");
	return (0);
}
