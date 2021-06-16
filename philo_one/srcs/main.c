/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/09 15:18:28 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 *			4 310 200 100
 *			4 410 200 200
 *			5 800 200 200 7
 *			5 800 200 200
 */


/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	free_destroy(t_philo *philo, t_args *args)
{
	int	i;

	(void)philo;
	i = 0;
	//args = philo->args;
	printf("NB FILOS DENTRO FREE DESTRY = %d\n", args->nb_philos);
	while (i < args->nb_philos)
	{
		//free(philo[i].fork_left);
		pthread_mutex_destroy(&philo[i].fork_left);
		i++;
	}
	//free(&philo->thread);
	free(philo);
}

/*
 * Either pthread_join(3) or pthread_detach() should be called for each thread
 * that an application creates, so that system resources for the thread can be
 * released.
 */

void	terminate_threads(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
//	printf("NUMBER PHILOS JOIN = %d\n", args->nb_philos);
	while (i < args->nb_philos)
	{
		pthread_join(philo[i].thread, NULL);
		//if (pthread_join(philo[i].thread, NULL) != 0)//do an if, in case it fails
		//	return ;
	}
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
	t_philo	*philo;
	t_args	args;

	if (argc == 5 || argc == 6 || argc == 7)
	{
		// NEED MORE MUTEX? FOR WHEN WRITING ON STDOUT/DISPLAY OR FOR WHEN A PHILO IS EATING
		if (ft_strcmp(argv[1], "-dt") == 0)
			init_args_dt(&args, argv);
		else
			init_args(&args, argv);

		printf("NUMBER PHILOS MAIN = %d\n", args.nb_philos);

		if (!(philo = (t_philo *)malloc(sizeof(t_philo) * args.nb_philos)))
			return (-1);
		init_philo(philo, &args);

		init_mutex_fork(philo, &args);

		printf("dt == %d\n", args.dt);
		if (init_pthread_philos(philo, &args) == FAIL)
			error_msg("The thread could not be created");
		terminate_threads(philo, &args);
		free_destroy(philo, &args);
	}

	philo = NULL;
	return (0);
}
