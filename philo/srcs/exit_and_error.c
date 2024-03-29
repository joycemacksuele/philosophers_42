/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/07 18:44:09 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * destroyroyng all mutex created and freeing any memory allocated.
 */

void	terminate_mutexes(t_const_data *const_data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&const_data->check_death);
	pthread_mutex_destroy(&const_data->print_action);
	while (i < const_data->nb_philos)
	{
		pthread_mutex_destroy(&const_data->fork[i]);
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
	else
		printf("%s\n", err_msg);
}
