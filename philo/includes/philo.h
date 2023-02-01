/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:07:48 by ltuffery          #+#    #+#             */
/*   Updated: 2023/02/01 18:47:58 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		body;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				populations;
	pthread_mutex_t	*forks;
}	t_data;

int	ft_atoi(const char *nptr);

#endif
