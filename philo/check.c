/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:16:43 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/05 17:08:49 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <unistd.h>

int	check_someone_is_die(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_simulation_guard);
	if (*philo->stop_simulation)
	{
		pthread_mutex_unlock(philo->stop_simulation_guard);
		return (1);
	}
	pthread_mutex_unlock(philo->stop_simulation_guard);
	return (0);
}

int	check_eat(t_philo *philo)
{
	int	ret;

	ret = 0;
	if (check_someone_is_die(philo))
		ret = 1;
	if (philo->times.last_lunch != -1)
	{
		if (timestamp() > philo->times.last_lunch + philo->times.u_die)
			ret = 1;
	}
	else if (philo->start_simulation + philo->times.u_die < timestamp())
		ret = 1;
	if (ret == 1)
		die_philo(philo);
	return (ret);
}
