/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:36:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/02/08 16:39:55 by ltuffery         ###   ########.fr       */
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
	// printf("%i | %s\n", philo->id, "Create");
	usleep(6000);
	eat_philo(philo);
	return (arg);
}

void	eat_philo(t_philo *philo)
{
	if ((philo->id % 2) == 1)
		usleep(philo->times.u_eat * 1000 * 2);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	// printf("%i | Eat\n", philo->id);
	usleep(philo->times.u_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
	data->forks = malloc(sizeof(int) * data->populations);
	if (data->forks == NULL)
	{
		free(data->philos);
		return ;
	}
	while (i < data->populations)
	{
		if (i > 0)
			data->philos[i - 1].fork.right = &data->philos[i].fork.left;
		pthread_mutex_init(&data->philos[i].fork.left, NULL);
		data->forks[i] = 0;
		data->philos[i].fork.left_status = &data->forks[i];
		data->philos[i].id = i + 1;
		data->philos[i].times.u_die = ft_atoi(av[2]);
		data->philos[i].times.u_eat = ft_atoi(av[3]);
		data->philos[i].times.u_sleep = ft_atoi(av[4]);
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
	create_philo(&data, av);
	meeting_philo(&data);
	free(data.philos);
}
