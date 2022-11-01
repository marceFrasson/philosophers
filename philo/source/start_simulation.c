/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/01 04:30:01 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		philo = table->philos + i;
		philo->index = i;
		philo->table = table;
		philo->left_fork = table->forks + i;
		philo->right_fork = table->forks + i + 1;
	}
	philo->right_fork = table->forks;
}

static void	*simulation(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->last_meal = philo->table->start;
	if (philo->index % 2)
		sleep_ms(2);
	while (TRUE)
	{
		if (philo->table->deaths || philo->table->stop)
			break ;
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (philo->times_eaten == philo->table->times_a_philo_must_eat)
			break ;
		sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	death_thread;
	int			i;

	i = -1;
	table->start = current_time();
	while (++i < table->number_of_philos)
		if (pthread_create(&(table->philos + i)->thread, NULL, &simulation,
				table->philos + i))
			return (1);
	if (pthread_create(&death_thread, NULL, &continue_or_end, table))
		return (1);
	i = -1;
	while (++i < table->number_of_philos)
		if (pthread_join((table->philos + i)->thread, NULL))
			return (1);
	if (pthread_join(death_thread, NULL))
		return (1);
	if (!table->deaths)
		printf("\nfull stomach philosophers\n");
	return (0);
}
