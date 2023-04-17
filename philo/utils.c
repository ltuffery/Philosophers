/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:39:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/17 14:18:08 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "includes/philo.h"
#include <stdio.h>
#include <unistd.h>

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

void	display(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->typing);
	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		pthread_mutex_unlock(philo->typing);
		return ;
	}
	pthread_mutex_unlock(philo->stop_simulation_guard);
	printf("%lli %i %s\n", timestamp() - philo->start_simulation, \
			philo->id, message);
	pthread_mutex_unlock(philo->typing);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long long	start;

	start = timestamp();
	while ((timestamp() - start) * 1000 < ms)
	{
		if (check_eat(philo))
			break ;
		usleep(500);
	}
}
