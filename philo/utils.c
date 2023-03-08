/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:39:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/08 12:29:24 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "includes/philo.h"
#include <stdio.h>
#include <signal.h>

long long	timestamp(void)
{
	struct timeval	val;

	gettimeofday(&val, NULL);
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

void	settimes(t_philo *philo, char **av)
{
	philo->times.u_die = ft_atoi(av[2]);
	philo->times.u_eat = ft_atoi(av[3]);
	philo->times.u_sleep = ft_atoi(av[4]);
	philo->times.last_lunch = -1;
}

void	display(t_philo *philo, t_messages message)
{
	char	*sentences[6];

	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		return ;
	}
	pthread_mutex_unlock(philo->stop_simulation_guard);
	sentences[0] = "has taken a fork";
	sentences[1] = "is eating";
	sentences[2] = "is sleeping";
	sentences[3] = "is thinking";
	sentences[4] = "died";
	pthread_mutex_lock(philo->typing);
	printf("%lli %i %s\n", timestamp() - philo->start_simulation, \
			philo->id, sentences[message]);
	pthread_mutex_unlock(philo->typing);
}
