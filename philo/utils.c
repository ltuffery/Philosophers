/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:39:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/07 10:04:23 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "includes/philo.h"
#include <stdio.h>
#include <signal.h>

int	timestamp(void)
{
	struct timeval	val;

	gettimeofday(&val, NULL);
	return (val.tv_usec * 1000);
}

void	settimes(t_philo *philo, char **av)
{
	philo->times.u_die = ft_atoi(av[2]);
	philo->times.u_eat = ft_atoi(av[3]);
	philo->times.u_sleep = ft_atoi(av[4]);
}

void	display(t_philo *philo, t_messages message)
{
	char	*sentences[6];

	sentences[0] = "has taken a fork";
	sentences[1] = "is eating";
	sentences[2] = "is sleeping";
	sentences[3] = "is thinking";
	sentences[4] = "died";
	pthread_mutex_lock(philo->typing);
	printf("%i %i %s\n", timestamp(), philo->id, sentences[message]);
	pthread_mutex_unlock(philo->typing);
}
