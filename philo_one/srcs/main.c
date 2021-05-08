/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/08 03:21:33 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	free_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		free(philo[i].fork);
		i++;
	}
//	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo			philo;

	if (argc == 5 || argc == 6)
	{
		init_args(&philo, argv);
		init_mutex_fork(&philo);
		// NEED MORE MUTEX? FOR WHEN WRITING ON STDOUT/DISPLAY OR FOR WHEN A PHILO IS EATING
		philo.start_time = get_time();// returns the current time in ms
		printf("STAR_TIME = %ld\n", philo.start_time);
		init_pthread_philos(&philo);
		free_philos(&philo);
	}
	return (0);
}

