/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/12 21:57:21 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	free_destroy(t_philo *philo, t_checker *checker, int nb_philos)
{
	int	i;

	(void)philo;
	i = 0;
	//args = philo->args;
	//printf("NB FILOS DENTRO FREE DESTRY = %d\n", nb_philos);
	while (i < nb_philos)
	{
		//free(philo[i].fork_left);
	//	pthread_mutex_destroy(&philo[i].fork_left);
		pthread_mutex_destroy(philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(&philo->print_action);
	pthread_mutex_destroy(&checker->check_death);
	//free(&philo->thread);
	//free(philo);
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
		i++;
		//	return ;
	}
}

void	error_msg(char *err_msg, int args_accepted)
{
	printf("%s\n", err_msg);
	if (args_accepted)
	{
		printf(COLOR_YELLOW);
		printf("Optional: -dt (flag to check status' time difference)\n");
		printf(COLOR_GREEN);
		printf("number_of_philosophers\n");
		printf("time_to_die\n");
		printf("time_to_eat\n");
		printf("time_to_sleep\n");
		printf(COLOR_YELLOW);
		printf("Optional: number_of_times_each_philosopher_must_eat\n");
		printf(COLOR_RESET);
	}
}


int	init(t_philo *philo, t_args *args, t_checker *checker, char **argv)
{
	int		ret_init_arg;

	ret_init_arg = 0;
	if (ft_strcmp(argv[1], "-dt") == 0)
		ret_init_arg = init_args_checker_diff_time(args, checker, argv);
	else
		ret_init_arg = init_args_checker(args, checker, argv);
	if (ret_init_arg == FAIL)
	{
		error_msg("Arguments accepted:\n-------------------", 1);
		return (FAIL);
	}
	init_philo(philo, args);
	init_mutex_fork(philo, args, checker);
	if (init_pthread_philos(philo, args, checker) == FAIL)
	{
		error_msg("The threads could not be created", 0);
		return (FAIL);
	}
	return (SUCCESS);
}

/*
 * get_time() returns an unsigned long for the current time in ms
 *
 * OBS.: If I did not know that the max number of philos had to be 200, I
 * would have to malloc the philo struct.
 * if (!(philo = (t_philo *)malloc(sizeof(t_philo) * args.nb_philos)))
 *		return (FAIL);
 */

int	main(int argc, char **argv)
{
	t_philo		philo[200];
	t_args		args;
	t_checker	checker;

	if (argc == 5 || argc == 6 || argc == 7)
	{
		print_status_header(philo->print_action);
		if (init(philo, &args, &checker, argv) == FAIL)
		{
			printf("RETORNOU FAIL P MAIN\n");
			return (FAIL);
		}
		terminate_threads(philo, &args);
		free_destroy(philo, &checker, args.nb_philos);
		printf("|---------------------------------------------------------|\n");
	}
	return (0);
}
