/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/01 04:20:17 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_memory(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

static int	alocate_memory(t_table *table)
{
	table->forks = NULL;
	table->philos = malloc(table->number_of_philos
			* sizeof(t_philo));
	if (!table->philos)
		return (1);
	table->forks = malloc(table->number_of_philos
			* sizeof(pthread_mutex_t));
	if (!table->forks)
		return (1);
	return (0);
}

static void	attribute_arguments_values(char **argv, t_table *table)
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->times_a_philo_must_eat = ft_atoi(argv[5]);
	else
		table->times_a_philo_must_eat = -1;
	table->start = 0;
	table->stop = 0;
}

static int	check_number_of_arguments(int argc)
{
	if (argc < 5 || argc > 6)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_number_of_arguments(argc))
	{
		printf("\nInvalid number of arguments.\
		\nTotal arguments: 4 or 5.\n\n\
		1. number_of_philosophers\n\
		2. time_to_die\n\
		3. time_to_eat\n\
		4. time_to_sleep\n\
		5. number_of_times_each_philosopher_must_eat (<- optional)\n\n");
		return (1);
	}
	attribute_arguments_values(argv, &table);
	if (alocate_memory(&table))
	{
		free_memory(&table);
		return (1);
	}
	create_philo(&table);
	start_simulation(&table);
	free_memory(&table);
	return (0);
}
