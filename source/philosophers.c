/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/09/21 23:26:14 by mfrasson         ###   ########.fr       */
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

void    print(t_philosopher *philosopher, int function)
{
    if (function == LEFT)
        printf("%d took the left fork\n", philosopher->index);
    else if (function == RIGHT)
        printf("%d took the right fork\n", philosopher->index);
    else if (function == EAT)
        printf("%d is eating\n", philosopher->index);
    else if (function == SLEEP)
        printf("%d is sleeping\n", philosopher->index);
    else if (function == THINK)
        printf("%d is thinking\n", philosopher->index);
    else if (function == DEAD)
    {
        printf("%d died\n", philosopher->index);
        philosopher->table->deaths = 1;
    }
}

static void    *mutex(void *args)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher*)args;

    pthread_mutex_lock(philosopher->left_fork);
    print(philosopher, LEFT);
    pthread_mutex_lock(philosopher->right_fork);
    print(philosopher, RIGHT);
    
    print(philosopher, EAT);
    sleep(philosopher->table->time_to_eat);
    philosopher->last_eat = current_time();
    philosopher->times_eaten++;
    
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
    
    print(philosopher, SLEEP);
    sleep(philosopher->table->time_to_sleep);
    
    print(philosopher, THINK);

    return (NULL);
}

int	start_threading(t_table *table)
{
	int			i;

	table->start = current_time();
	i = -1;
	while (++i < table->number_of_philosophers)
		if (pthread_create(&(table->philosophers + i)->thread, NULL, &mutex,
				table->philosophers + i))
			return (1);
	i = -1;
	while (++i < table->number_of_philosophers)
		if (pthread_join((table->philosophers)->thread, NULL))
			return (2);
	return (0);
}

void    time_to_die(t_table *table)
{
    int i;
    
    i = -1;
    while (++i < table->number_of_philosophers)
        if (table->time_to_die < current_time() -
            (table->philosophers + i)->last_eat)
            mutex(table->philosophers + i);
    
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

/*

mutex_init

wait x thinking time
mutex_lock left fork
mutex_lock right fork
    print eating
wait x eating time
mutex_unlock left fork
mutex_unlock right fork
wait x sleeping time

pthread_create
pthread_exit

mutex_destroy

pthread_exit

*/