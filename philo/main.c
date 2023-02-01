/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:36:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/02/01 18:56:54 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%i | %s\n", philo->id, "il mange");
	return (arg);
}

void	die_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->populations)
	{
		pthread_join(data->philos[i].body, NULL);
		i++;
	}
}

void	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->populations);
	if (data->philos == NULL)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->populations);
	if (data->forks == NULL)
	{
		free(data->philos);
		return ;
	}
	while (i < data->populations)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i;
		pthread_create(&data->philos[i].body, NULL, \
				routine, &data->philos[i]);
		usleep(1);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	data.populations = ft_atoi(av[1]);
	create_philo(&data);
	die_philo(&data);
	free(data.philos);
}
