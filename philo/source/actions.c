/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:07 by mfrasson          #+#    #+#             */
/*   Updated: 2022/11/04 01:13:03 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print(philo, FORK);
}

void	eat(t_philo *philo)
{
	print(philo, EAT);
	pthread_mutex_lock(philo->table->eating);
	philo->last_meal = current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->table->eating);
	sleep_ms(philo->table->time_to_eat);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	take_a_nap(t_philo *philo)
{
	print(philo, SLEEP);
	sleep_ms(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print(philo, THINK);
}
