/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/27 21:52:32 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *						void *(*start_routine) (void *), void *arg);
 *
 *
 *	Creating the same amount of the "number_of_philosopher" input, of threads
 *	on the program  and calling the tf_philo_actions (tf = thread functions),
 *	whithe the index of the structure as it's only paramenter.
 */

int	init_pthread_philos(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	while (i < const_data->nb_philos && const_data->time_to_die >= 0)
	{
		philo[i].const_data = const_data;
		if (pthread_create(&(philo[i].thread), NULL, tf_philo_actions,
			&(philo[i])))
		{
			error_msg("The threads could not be created", 0);
			return (FAIL);
		}
		pthread_detach(philo[i].thread);
		i++;
	}
	check_death(&philo[0], const_data);
	return (SUCCESS);
}

/*
 * Initializating a mutex to each fork (which is the "number_of_philosopher"
 * given as input by the user).
 *
 * int	pthread_mutex_init(pthread_mutex_t *mutex,
 *										const pthread_mutexattr_t *mutexattr);
 *
 * The philo->printf mutex is to lock a thread to write on the screen while
 * another thread is already doing it, so we don't have scrambled output.
 *
 * The philo->check_death is to lock a philo thread to do anything (mainly
 * eating) at the same time s/he has died.
 */

int	init_mutex_fork(t_const_data *const_data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&const_data->print_action, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(&const_data->check_death, NULL) != 0)
		return (FAIL);
	while (i < const_data->nb_philos)
	{
		if (pthread_mutex_init(&const_data->fork[i], NULL) != 0)
			return (FAIL);
	//	if (pthread_mutex_init(philo[i].print_action, NULL) != 0)
	//		return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	init_args_checker_diff_time(t_const_data *const_data, char **argv)
{
	const_data->nb_philos = ft_atoi(argv[2]);
	const_data->time_to_die = ft_atoi(argv[3]);
	const_data->time_to_eat = ft_atoi(argv[4]);
	const_data->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6])
		const_data->times_philo_must_eat = ft_atoi(argv[6]);
	else
		const_data->times_philo_must_eat = FALSE;
	const_data->start_time = get_current_time();
	const_data->one_philo_died = FALSE;
	//const_data->satisfied = FALSE;
	const_data->diff_time_arg = TRUE;
	if (const_data->nb_philos < 1 || const_data->nb_philos > 200 || const_data->time_to_die < 0 ||
		const_data->time_to_eat < 0 || const_data->time_to_sleep < 0 ||
		const_data->times_philo_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
}

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

int	init_args_checker(t_const_data *const_data, char **argv)
{
	const_data->nb_philos = ft_atoi(argv[1]);
	const_data->time_to_die = ft_atoi(argv[2]);
	const_data->time_to_eat = ft_atoi(argv[3]);
	const_data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		const_data->times_philo_must_eat = ft_atoi(argv[5]);
	else
		const_data->times_philo_must_eat = FALSE;
	const_data->start_time = get_current_time();
	const_data->one_philo_died = FALSE;
	//const_data->satisfied = FALSE;
	const_data->diff_time_arg = FALSE;
	if (const_data->nb_philos < 1 || const_data->nb_philos > 200 || const_data->time_to_die < 0 ||
		const_data->time_to_eat < 0 || const_data->time_to_sleep < 0 ||
		const_data->times_philo_must_eat < 0)
		return (FAIL);
	//printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", const_data->nb_philos, const_data->time_to_die, const_data->time_to_eat, const_data->time_to_sleep, const_data->times_philo_must_eat);
	return (SUCCESS);
}

void	init_forks(t_philo *philo, int nb_philos, int philo_position)
{
	if (philo_position == 1)
	{
		philo->left_fork = 2;
		philo->right_fork = 1;
	}
	else if (philo_position == nb_philos)
	{
		philo->left_fork = 1;
		philo->right_fork = nb_philos;
	}
	else
	{
		philo->left_fork = philo_position + 1;
		philo->right_fork = philo_position;
	}
}

void	init_philo(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	while (i < const_data->nb_philos)
	{
		philo[i].position = i + 1;
		init_forks(&philo[i], const_data->nb_philos, philo[i].position);
		philo[i].ate = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].satisfied = FALSE;
		i++;
	}
}
