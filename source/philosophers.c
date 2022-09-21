/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/09/21 20:11:34 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int check_number_of_arguments(int argc)
{
    if (argc < 5 || argc > 6)
        return (1);
    return (0);
}

void   attribute_arguments_values(char **argv, t_table *table)
{
    table->number_of_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    printf("\nnumber_of_philosophers: %i\ntime_to_die: %i\ntime_to_eat: %i\n\
        time_to_sleep: %i\n", table->number_of_philosophers, table->time_to_die,
        table->time_to_eat, table->time_to_sleep);
    if (argv[5])
    {
        table->times_a_philosopher_must_eat = ft_atoi(argv[5]);
        printf("times_a_philosopher_must_eat: %i\n\n",
            table->times_a_philosopher_must_eat);
    }
    else
    {
        table->times_a_philosopher_must_eat = 0;
        printf("\n");
    }
    table->start = 0;
}

static void	*instructions(void *args)
{
	t_philosopher *philosopher;

    philosopher = (t_philosopher*)args;
    printf("philosopher %d eats\n", philosopher->index);
    sleep(philosopher->table->time_to_eat);
    printf("philosopher %d sleeps\n", philosopher->index);
    sleep(philosopher->table->time_to_sleep);
    printf("philosopher %d thinks\n", philosopher->index);
    sleep(philosopher->table->time_to_eat - philosopher->table->time_to_sleep + 1);
	return (NULL);
}

int	start_threading(t_table *table)
{
	int			i;

	table->start = current_time();
	i = -1;
	while (++i < table->number_of_philosophers)
		if (pthread_create(&(table->philosophers + i)->thread, NULL, &instructions,
				table->philosophers + i))
			return (1);
	i = -1;
	while (++i < table->number_of_philosophers)
		if (pthread_join((table->philosophers)->thread, NULL))
			return (2);
	return (0);
}

static void	create_philosopher(t_table *table)
{
	t_philosopher	*philosopher;
	int		i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philosopher = table->philosophers + i;
        philosopher->index = i;
		philosopher->table = table;
		philosopher->left_fork = table->forks + i;
		philosopher->right_fork = table->forks + i + 1;
	}
	philosopher->right_fork = table->forks;
}

static int	alocate_memory(t_table *table)
{
	int	i;

	table->forks = NULL;
	table->philosophers = malloc(table->number_of_philosophers * sizeof(t_philosopher));
	if (!table->philosophers)
		return (1);
    table->forks = malloc(table->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (1);
	return (0);
}

void    free_memory(t_table *table)
{
    free(table->philosophers);
    free(table->forks);
}

int main(int argc, char **argv)
{
    t_table table;

    if (check_number_of_arguments(argc))
    {
        printf("\nInvalid number of arguments.\nTotal arguments: 4 or 5.\n\n\
        1. number_of_philosophers\n 2. time_to_die\n 3. time_to_eat\n\
        4. time_to_sleep\n*5. times_a_philosopher_must_eat   \
        (<- optional)\n\n");
        return (1);
    }
    attribute_arguments_values(argv, &table);
    if (alocate_memory(&table))
    {
        free_memory(&table);
        return (1);
    }
    create_philosopher(&table);
    start_threading(&table);

    return (0);
}

//criar função que print ele dormindo depois comendo e pensando efaz as threads rodarem esse cara