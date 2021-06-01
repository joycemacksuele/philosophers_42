/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/01 02:10:14 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	free_destroy(t_philo *philo, t_args *args)
{
	int	i;

	(void)philo;
	i = 1;
//	pthread_mutex_destroy(philo->fork);// why only one destroy???
	free(args->forks);
	while (i < args->nb_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
//	free(philo);
}

/*
 * Either pthread_join(3) or pthread_detach() should be called for each thread
 * that an application creates, so that system resources for the thread can be
 * released.
 */

void	terminate_threads(t_philo *philo, t_args *args)
{
	int	i;

	i = 1;
	while (i <= args->nb_philos)
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
	t_args	args;

	if (argc == 5 || argc == 6 || argc == 7)
	{
		// NEED MORE MUTEX? FOR WHEN WRITING ON STDOUT/DISPLAY OR FOR WHEN A PHILO IS EATING
		if (ft_strcmp(argv[1], "-dt") == 0)
			init_args_dt(&philo, &args, argv);
		else
			init_args(&philo, &args, argv);

		init_mutex_fork(&philo, &args);

		printf("dt == %d\n", args.dt);
		if (init_pthread_philos(&philo, &args) == FAIL)
			error_msg("The thread could not be created");
		terminate_threads(&philo, &args);
		free_destroy(&philo, &args);
	}
	return (0);
}
