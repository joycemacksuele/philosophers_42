/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/27 03:59:15 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	free_destroy(t_philo *philo)//, t_args *args)
{
	int	i;

	i = 1;
//	pthread_mutex_destroy(philo->fork);// why only one destroy???
	//free(philo->forks);
	while (i <= philo[0].nb_philos)
	{
		pthread_mutex_destroy(&philo[i].forks);
		i++;
	}
//	free(philo);
}

/*
 * Either pthread_join(3) or pthread_detach() should be called for each thread
 * that an application creates, so that system resources for the thread can be
 * released.
 */

void	terminate_threads(t_philo *philo)//, t_args *args)
{
	int	i;

	i = 1;
	while (i <= philo[0].nb_philos)
		pthread_join(philo[i].thread, NULL);//do an if, in case it fails
}

void	error_msg(char *err_msg)
{
	printf("%s\n", err_msg);
}

/*
 * get_time() returns an unsigned long for the current time in ms
 */

int	main(int argc, char **argv)
{
	t_philo	philo;
//	t_args	args;

	if (argc == 5 || argc == 6 || argc == 7)
	{
		init_mutex_fork(&philo);//, &args);
		// NEED MORE MUTEX? FOR WHEN WRITING ON STDOUT/DISPLAY OR FOR WHEN A PHILO IS EATING
		if (ft_strcmp(argv[1], "-dt") == 0)
			init_args_dt(&philo, argv);
		else
			init_args(&philo, argv);

		printf("dt == %d\n", philo.dt);
		if (init_pthread_philos(&philo) == FAIL)
			error_msg("The thread could not be created");
		terminate_threads(&philo);//, &args);
		free_destroy(&philo);//, &args);
	}
	return (0);
}
