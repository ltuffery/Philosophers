/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:23:24 by ltuffery          #+#    #+#             */
/*   Updated: 2023/01/29 16:49:26 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>

void	*test(void *id)
{
	printf("%i", *(int *)id);
}

int	main(int ac, char **av)
{
	pthread_t	tid;

	if (ac < 5 || ac > 6)
		return (1);
	pthread_create(&tid, NULL, test, (void *)&tid);
}
