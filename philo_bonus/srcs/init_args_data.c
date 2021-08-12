/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/11 22:38:15 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * number_of_philosophers:
 * Is the number of philosophers and also the number of forks.
 *
 *
 * In milliseconds:
 *
 * time_to_die:
 * If a philosopher doesn’t start eating ’time_to_die’ milliseconds after
 * starting his last meal or the beginning of the simulation, s/he dies.
 *
 * time_to_eat:
 * The time it takes for a philo to eat. During that time the two forks are kept.
 *
 * time_to_sleep:
 * Is the time the philosopher will spend sleeping.
 *
 * number_of_times_each_philosopher_must_eat (argument is optional):
 * If all philosophers eat at least ’number_of_times_each_philosopher_must_eat’
 * the simulation will stop.
 * If not specified, the simulation will stop only at the death of a philosopher.
 *
 */

int	init_data_diff_time(t_const_data *const_data, char **argv)
{
	const_data->nb_philos = ft_atoi(argv[2]);
	const_data->time_to_die = ft_atoi(argv[3]);
	const_data->time_to_eat = ft_atoi(argv[4]);
	const_data->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6])
		const_data->times_philo_must_eat = ft_atoi(argv[6]);
	else
		const_data->times_philo_must_eat = FALSE;
	//const_data->start_time = get_current_time();
	const_data->one_philo_died = FALSE;
	const_data->diff_time_arg = TRUE;
	if (const_data->nb_philos < 1 || const_data->nb_philos > 200
		|| const_data->time_to_die < 0
		|| const_data->time_to_eat < 0 || const_data->time_to_sleep < 0
		|| const_data->times_philo_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
}

int	init_data(t_const_data *const_data, char **argv)
{
	const_data->nb_philos = ft_atoi(argv[1]);
	const_data->time_to_die = ft_atoi(argv[2]);
	const_data->time_to_eat = ft_atoi(argv[3]);
	const_data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		const_data->times_philo_must_eat = ft_atoi(argv[5]);
	else
		const_data->times_philo_must_eat = FALSE;
	//const_data->start_time = get_current_time();
	const_data->one_philo_died = FALSE;
	const_data->diff_time_arg = FALSE;
	if (const_data->nb_philos < 1 || const_data->nb_philos > 200
		|| const_data->time_to_die < 0
		|| const_data->time_to_eat < 0 || const_data->time_to_sleep < 0
		|| const_data->times_philo_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
}

void	init_philo(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	while (i < const_data->nb_philos)
	{
		philo[i].position = i + 1;
		philo[i].ate = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].satisfied = FALSE;
		i++;
	}
}
