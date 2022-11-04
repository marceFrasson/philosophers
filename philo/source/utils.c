/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/04 01:10:42 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	double			num;
	int				sinal;

	i = 0;
	num = 0;
	sinal = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sinal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (sinal * num);
}

long int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_ms(int time)
{
	usleep(time * 1000);
}

void	print(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->table->printing);
	if (!philo->table->deaths)
	{
		if (action == FORK)
			printf("\033[0;34m%ld %d has taken a fork\n", current_time()
				- philo->table->start, philo->index);
		else if (action == EAT)
			printf("\033[0;36m%ld %d is eating\n", current_time()
				- philo->table->start, philo->index);
		else if (action == SLEEP)
			printf("\033[0;35m%ld %d is sleeping\n", current_time()
				- philo->table->start, philo->index);
		else if (action == THINK)
			printf("\033[0;37m%ld %d is thinking\n", current_time()
				- philo->table->start, philo->index);
		else if (action == DEAD)
		{
			printf("\033[0;31m%ld %d died\n", current_time()
				- philo->table->start, philo->index);
			philo->table->deaths++;
		}
	}
	pthread_mutex_unlock(philo->table->printing);
}
