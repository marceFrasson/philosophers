/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/01 02:41:09 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    free_memory(t_table *table)
{
    free(table->philos);
    free(table->forks);
}

void    sleep_ms(int time)
{
    usleep(time * 1000);
}

void    print(t_philo *philo, int action)
{
    if (!philo->table->deaths)
    {
        if (action == FORK)
            printf("\033[0;34m%ld %d has taken a fork\n", current_time() - philo->table->start,
                philo->index);
        else if (action == EAT)
            printf("\033[0;36m%ld %d is eating\n", current_time() - philo->table->start, philo->index);
        else if (action == SLEEP)
            printf("\033[0;35m%ld %d is sleeping\n", current_time()- philo->table->start, philo->index);
        else if (action == THINK)
            printf("\033[0;37m%ld %d is thinking\n", current_time()- philo->table->start, philo->index);
        else if (action == DEAD)
        {
            printf("\033[0;31m%ld %d died\n", current_time()- philo->table->start, philo->index);
            philo->table->deaths++;
        }
    }
}

int    time_to_stop(t_table *table)
{
    t_philo philo;
    int i;

    i = -1;
    while (++i < table->number_of_philos)
    {
        philo = table->philos[i];
        if (philo.table->times_a_philo_must_eat >= 0 
            && philo.times_eaten >= philo.table->times_a_philo_must_eat)
        {
            philo.table->stop++;
            printf("philosopher %d full stomach\n", philo.index);
            return (1);
        }
    }
    return (0);
}

int time_to_die(t_table *table)
{
    t_philo philo;
    int     i;

    i = -1;
    while (++i < table->number_of_philos)
    {
        philo = table->philos[i];
        if (current_time() - philo.last_meal > philo.table->time_to_die)
        {
            print(&philo, DEAD);
            return (1);
        }
    }
    return (0);
}

void    *continue_or_end(void *args)
{
    t_table *table;

    table = (t_table *)args;
    while (true) 
    {
        sleep_ms(1);
        if (time_to_die(table))
            break;
        if (time_to_stop(table))
            break;
    }
    return (NULL);
}

static void    *simulation(void *args)
{
    t_philo *philo;

    philo = (t_philo*)args;
    philo->last_meal = philo->table->start;
    if (philo->index % 2)
        sleep_ms(2);
    while (true)
    {
        if (philo->table->deaths || philo->table->stop)
            break;
        pthread_mutex_lock(philo->left_fork);
        print(philo, FORK);
        pthread_mutex_lock(philo->right_fork);  
        print(philo, FORK);
        print(philo, EAT);
        philo->last_meal = current_time();
        sleep_ms(philo->table->time_to_eat);
        philo->times_eaten++;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        print(philo, SLEEP);
        sleep_ms(philo->table->time_to_sleep);

        print(philo, THINK);
    }
    return (NULL);
}

int	start_simulation(t_table *table)
{
    pthread_t   death_thread;
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
		if (pthread_join(table->philos->thread, NULL))
			return (1);
    if (pthread_join(death_thread, NULL))
        return (1);
    if (!table->deaths)
        printf("Todo mundo comeu");
    return (0);
}

static void	create_philo(t_table *table)
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

void   attribute_arguments_values(char **argv, t_table *table)
{
    table->number_of_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);

    if (argv[5])
    {
        table->times_a_philo_must_eat = ft_atoi(argv[5]);
        printf("times_a_philo_must_eat: %i\n\n",
            table->times_a_philo_must_eat);
    }
    else
    {
        table->times_a_philo_must_eat = -1;
        printf("\n");
    }
    table->start = 0;
    table->stop = 0;
}

int check_number_of_arguments(int argc)
{
    if (argc < 5 || argc > 6)
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_table table;

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

/*

time to die

    =

if last meal
    last meal > time to die
else
    time to die - start <= 0

    ;

time to stop

    =

times_eaten >= times_must_eat

    ;

*/
