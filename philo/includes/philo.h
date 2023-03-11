/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:07:48 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/11 11:12:51 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define TAKEN "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_times
{
	int	u_eat;
	int	u_sleep;
	int	u_die;
	int	last_lunch;
}	t_times;

typedef struct s_philo
{
	int				id;
	pthread_t		body;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	t_times			times;
	pthread_mutex_t	*typing;
	long long		start_simulation;
	int				*stop_simulation;
	pthread_mutex_t	*stop_simulation_guard;
	int				number_of_meals;
	int				number_max_of_meals;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				populations;
	pthread_mutex_t	typing;
	int				stop_simulation;
	pthread_mutex_t	stop_simulation_guard;
}	t_data;

/*	UTILS	*/
int			ft_atoi(const char *nptr);
void		settimes(t_philo *philo, char **av);
long long	timestamp(void);
void		display(t_philo *philo, char *message);

/*	CLEAN	*/
void		data_clean(t_data *data);

/*	ROUTINE	*/
void		eat_philo(t_philo *philo);
int			check_kill(t_philo *philo);
void		die_philo(t_philo *philo);

#endif
