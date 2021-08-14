/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 23:59:22 by whoami            #+#    #+#             */
/*   Updated: 2021/08/14 20:38:19 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_process(t_philo *philo, t_const_data *const_data)
{
	if (init_process_philos(philo, const_data) == FAIL)
	{
		error_msg("The threads could not be created", 0);
		return (FAIL);
	}
	return (SUCCESS);
}

int	init_struct(t_philo *philo, t_const_data *const_data, char **argv)
{
	int		ret_init_arg;

	ret_init_arg = 0;
	ret_init_arg = init_data(const_data, argv);
	if (ret_init_arg == FAIL)
		return (FAIL);
	init_philo(philo, const_data);
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
	t_philo			philo[200];
	t_const_data	const_data;

	if (argc >= 5 || argc == 6)
	{
		if (init_struct(philo, &const_data, argv) == FAIL)
			return (FAIL);
		init_semaphores(&const_data);
		print_status_header(0);
		if (init_process(philo, &const_data) == FAIL)
			return (FAIL);
		print_status_header(1);
	}
	else
		error_msg("", 1);
	return (0);
}
