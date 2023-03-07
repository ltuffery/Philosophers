/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:07:48 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/07 09:59:58 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef enum e_messages
{
	TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_messages;

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
	pthread_mutex_t	*right;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		body;
	t_fork			fork;
	t_times			times;
	pthread_mutex_t	*typing;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				populations;
	pthread_mutex_t	typing;
}	t_data;

/*	UTILS	*/
int		ft_atoi(const char *nptr);
void	settimes(t_philo *philo, char **av);
int		timestamp(void);
void	display(t_philo *philo, t_messages message);

#endif
