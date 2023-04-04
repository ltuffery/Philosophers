/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:16:43 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/15 12:37:25 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_sleep(t_philo *philo)
{
	if (philo->times.last_lunch != -1)
	{
		if (timestamp() + philo->times.u_sleep > \
				philo->times.last_lunch + philo->times.u_die)
			return (1);
	}
	else
	{
		if (timestamp() + philo->times.u_sleep > \
				philo->start_simulation + philo->times.u_die)
			return (1);
	}
	return (0);
}

int	check_eat(t_philo *philo)
{
	if (philo->times.last_lunch != -1)
	{
		printf("%lli\n", philo->times.last_lunch + philo->times.u_die);
		if (timestamp() > philo->times.last_lunch + philo->times.u_die)
			return (1);
		if (timestamp() + philo->times.u_eat > \
				philo->times.last_lunch + philo->times.u_die)
			return (1);
	}
	else
	{
		if (philo->start_simulation + philo->times.u_die < timestamp())
			return (1);
		if (timestamp() + philo->times.u_eat > \
				philo->start_simulation + philo->times.u_die)
			return (1);
	}
	return (0);
}
