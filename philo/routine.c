/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:27:52 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/17 14:56:16 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	die_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		return ;
	}
	*philo->stop_simulation = 1;
	pthread_mutex_unlock(philo->stop_simulation_guard);
	pthread_mutex_lock(philo->typing);
	printf("%lli %i died\n", timestamp() - philo->start_simulation, philo->id);
	pthread_mutex_unlock(philo->typing);
}

void	sleep_philo(t_philo *philo)
{
	if (check_someone_is_die(philo))
		return ;
	display(philo, SLEEP);
	ft_usleep(philo->times.u_sleep * 1000, philo);
	eat_philo(philo);
}

void	eat_philo(t_philo *philo)
{
	if (check_meals(philo))
		return ;
	if (check_eat(philo))
		return ;
	display(philo, THINK);
	pthread_mutex_lock(&philo->fork_left);
	display(philo, TAKEN);
	if (check_eat(philo))
	{
		pthread_mutex_unlock(&philo->fork_left);
		return ;
	}
	pthread_mutex_lock(philo->fork_right);
	display(philo, TAKEN);
	display(philo, EAT);
	ft_usleep(philo->times.u_eat * 1000, philo);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->times.last_lunch = timestamp();
	philo->number_of_meals++;
	sleep_philo(philo);
}
