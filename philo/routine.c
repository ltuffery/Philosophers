/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:27:52 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/11 11:15:49 by ltuffery         ###   ########.fr       */
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
		*philo->stop_simulation = 1;
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
	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		return ;
	}
	pthread_mutex_unlock(philo->stop_simulation_guard);
	display(philo, SLEEP);
	usleep(philo->times.u_sleep * 1000);
	eat_philo(philo);
}

void	eat_philo(t_philo *philo)
{
	if (philo->times.last_lunch == -1)
	{
		if (timestamp() - philo->start_simulation > philo->times.u_die)
			die_philo(philo);
	}
	else if (philo->times.last_lunch + philo->times.u_die * 1000 < timestamp())
		die_philo(philo);
	if (philo->number_of_meals == philo->number_max_of_meals)
		return ;
	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		return ;
	}
	pthread_mutex_unlock(philo->stop_simulation_guard);
	display(philo, THINK);
	pthread_mutex_lock(&philo->fork_left);
	display(philo, TAKEN);
	pthread_mutex_lock(philo->fork_right);
	display(philo, TAKEN);
	display(philo, EAT);
	usleep(philo->times.u_eat * 1000);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->times.last_lunch = timestamp();
	philo->number_of_meals++;
	sleep_philo(philo);
}
