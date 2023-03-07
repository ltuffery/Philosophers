/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:07:48 by ltuffery          #+#    #+#             */
/*   Updated: 2023/02/08 16:39:00 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_times
{
	int	u_eat;
	int	u_sleep;
	int	u_die;
	int	last_action;
}	t_times;

typedef struct s_fork
{
	pthread_mutex_t	left;
	int				*left_status;
	pthread_mutex_t	*right;
	int				*right_status;
}	t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	body;
	t_fork		fork;
	t_times		times;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	int		populations;
	int		*forks;
}	t_data;

int	ft_atoi(const char *nptr);
int	timestamp(void);

#endif
