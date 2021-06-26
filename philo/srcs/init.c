/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/25 23:21:59 by whoami           ###   ########.fr       */
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

int	init_pthread_philos(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
//	printf("NB TOTAL PHILOS = %d\n", args->nb_philos);
	print_status_header(philo->print_action);
	while (i < args->nb_philos)// && args->time_to_die >= 0)
	{
		philo[i].args = args;
		if (pthread_create(&philo[i].thread, NULL, tf_philo_actions, &philo[i]))
			return (FAIL);
		//printf("thread created\n");
		i++;
	}
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

int	init_mutex_fork(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&philo->print_action, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(&philo->check_death, NULL) != 0)
		return (FAIL);
	while (i < args->nb_philos)
	{
		//philo[i].fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		//if (philo[i].fork_left == NULL)
		//	return (FAIL);
		if (pthread_mutex_init(&philo[i].fork[i], NULL) != 0)
			return (FAIL);
		//printf("mutex initialized\n");
		i++;
	}
/*	i = 0;
	while (i < args->nb_philos)
	{
		if (i == args->nb_philos - 1)// if its the last fork
			philo[i].fork_right = philo[0].fork_left;
		else
			philo[i].fork_right = philo[i + 1].fork_left;
		i++;
	}*/
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

int	init_args_diff_time(t_args *args, char **argv)
{
	args->diff_time = 1;
	args->nb_philos = ft_atoi(argv[2]);
	args->time_to_die = ft_atoi(argv[3]);
	args->time_to_eat = ft_atoi(argv[4]);
	args->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6])
		args->times_philo_must_eat = ft_atoi(argv[6]);
	else
		args->times_philo_must_eat = 0;
	if (args->nb_philos < 1 || args->nb_philos > 200 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0 ||
		args->times_philo_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", args->nb_philos, args->time_to_die, args->time_to_eat, args->time_to_sleep, args->times_philo_must_eat);
// TEST
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

int	init_args(t_args *args, char **argv)
{
	args->diff_time = 0;
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->times_philo_must_eat = ft_atoi(argv[5]);
	else
		args->times_philo_must_eat = 0;
	if (args->nb_philos < 1 || args->nb_philos > 200 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0 ||
		args->times_philo_must_eat < 0)
		return (FAIL);
	return (SUCCESS);
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", args->nb_philos, args->time_to_die, args->time_to_eat, args->time_to_sleep, args->times_philo_must_eat);
// TEST
}

void	init_philo(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		philo[i].position = i + 1;
		philo[i].start_time = get_current_time();
		philo[i].one_philo_died = 0;
		philo[i].last_meal_time = get_current_time();
		init_forks(&philo[i], args->nb_philos, philo[i].position);
//		printf("		nb[%d] = %d\nleft_fork = %d\nright_fork = %d\n", i, philo[i].position, philo[i].left_fork, philo[i].right_fork);
		i++;
	}
// TEST
	printf("START_TIME = %ld\n", philo->start_time);
// TEST
}
