/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:36:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/05 16:55:51 by ltuffery         ###   ########.fr       */
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
	if (philo->id % 2)
		usleep(20000);
	eat_philo(philo);
	return (arg);
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

void	philo_born(t_data *data, long long start_simulation, char **av)
{
	int	i;

	i = 0;
	while (i < data->populations)
	{
		pthread_mutex_init(&data->philos[i].fork_left, NULL);
		if (i > 0)
			data->philos[i - 1].fork_right = &data->philos[i].fork_left;
		data->philos[i].id = i + 1;
		data->philos[i].typing = &data->typing;
		data->philos[i].start_simulation = start_simulation;
		data->philos[i].stop_simulation = &data->stop_simulation;
		data->philos[i].stop_simulation_guard = &data->stop_simulation_guard;
		data->philos[i].number_of_meals = 0;
		data->philos[i].number_max_of_meals = -1;
		settimes(&data->philos[i], av);
		if (av[5] != NULL)
			data->philos[i].number_max_of_meals = ft_atoi(av[5]);
		if (i + 1 == data->populations)
			data->philos[i].fork_right = &data->philos[0].fork_left;
		i++;
	}
}

void	create_philo(t_data *data, char **av)
{
	int			i;
	long long	start_simulation;

	i = 0;
	start_simulation = timestamp();
	data->philos = malloc(sizeof(t_philo) * data->populations);
	if (data->philos == NULL)
		return ;
	philo_born(data, start_simulation, av);
	if (data->populations == 1)
	{
		display(&data->philos[0], THINK);
		display(&data->philos[0], TAKEN);
		usleep(data->philos[0].times.u_die * 1000);
		die_philo(&data->philos[0]);
		return ;
	}	
	while (i < data->populations)
	{
		pthread_create(&data->philos[i].body, NULL, routine, &data->philos[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	data.populations = ft_atoi(av[1]);
	data.stop_simulation = 0;
	pthread_mutex_init(&data.typing, NULL);
	pthread_mutex_init(&data.stop_simulation_guard, NULL);
	create_philo(&data, av);
	meeting_philo(&data);
	free(data.philos);
}
