/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/24 23:12:31 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	terminate_mutexes(t_const_data *const_data)
{
	int	i;

	i = 0;
	//printf("NB FILOS DENTRO FREE DESTRY = %d\n", const_data->nb_philos);
	pthread_mutex_destroy(&const_data->check_death);
	pthread_mutex_destroy(&const_data->print_action);
	while (i < const_data->nb_philos)
	{
		pthread_mutex_destroy(&const_data->fork[i]);
	//	pthread_mutex_destroy(philo[i].print_action);
		i++;
	}
}

/*
 * Either pthread_join(3) or pthread_detach() should be called for each thread
 * that an application creates, so that system resources for the thread can be
 * released.
 */

void	terminate_threads(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	while (i < const_data->nb_philos)
	{
		//pthread_join(philo[i].thread, NULL);
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("join error\n");
			return ;
		}
		i++;
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


int	init(t_philo *philo, t_const_data *const_data, char **argv)
{
	int		ret_init_arg;

	ret_init_arg = 0;
	if (ft_strcmp(argv[1], "-dt") == 0)
		ret_init_arg = init_args_checker_diff_time(const_data, argv);
	else
		ret_init_arg = init_args_checker(const_data, argv);
	if (ret_init_arg == FAIL)
		return (FAIL);
	init_philo(philo, const_data);
	init_mutex_fork(const_data);
	if (ft_strcmp(argv[1], "-dt") == 0)
		print_status_header_optional();
	else
		print_status_header();
	if (init_pthread_philos(philo, const_data) == FAIL)
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
 * if (!(philo = (t_philo *)malloc(sizeof(t_philo) * const_data.nb_philos)))
 *		return (FAIL);
 */

int	main(int argc, char **argv)
{
	t_philo		philo[200];
	t_const_data		const_data;
	//t_checker	checker;

	if (argc == 5 || argc == 6 || argc == 7)
	{
		if (init(philo, &const_data, argv) == FAIL)
			return (FAIL);
		terminate_threads(philo, &const_data);
		terminate_mutexes(&const_data);
		if (ft_strcmp(argv[1], "-dt") == 0)
		{
			printf("└───────────────┴─────────┴─────────────────────────┴");
			printf("───────────┘\n");
		}
		else
			printf("└───────────────┴─────────┴─────────────────────────┘\n");

	}
	return (0);
}
