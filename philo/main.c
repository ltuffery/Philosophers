/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:36:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/07 09:59:52 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	eat_philo(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(6000);
	eat_philo(philo);
	return (arg);
}

void	eat_philo(t_philo *philo)
{
	usleep(600 * (philo->id - 1));
	display(philo, TAKEN);
	pthread_mutex_lock(&philo->fork.left);
	pthread_mutex_lock(philo->fork.right);
	display(philo, EAT);
	usleep(philo->times.u_eat * 1000);
	pthread_mutex_unlock(&philo->fork.left);
	pthread_mutex_unlock(philo->fork.right);
}

void	meeting_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->populations)
	{
		pthread_join(data->philos[i].body, NULL);
		i++;
	}
}

void	create_philo(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->populations);
	if (data->philos == NULL)
		return ;
	while (i < data->populations)
	{
		if (i > 0)
			data->philos[i - 1].fork.right = &data->philos[i].fork.left;
		pthread_mutex_init(&data->philos[i].fork.left, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].typing = &data->typing;
		settimes(&data->philos[i], av);
		pthread_create(&data->philos[i].body, NULL, \
				routine, &data->philos[i]);
		i++;
	}
	data->philos[i - 1].fork.right = &data->philos[0].fork.left;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	data.populations = ft_atoi(av[1]);
	pthread_mutex_init(&data.typing, NULL);
	create_philo(&data, av);
	meeting_philo(&data);
	free(data.philos);
}
