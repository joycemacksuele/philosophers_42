/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/09 15:32:30 by jfreitas         ###   ########.fr       */
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
	//printf("NB TOTAL PHILOS = %d\n", args->nb_philos);
	printf("┌-------------------------------------------------------------┐\n");
	printf("| Time          | Philo   | Event                             |\n");
	printf("|-------------------------------------------------------------|\n");
	while (i < args->nb_philos)// && args->time_to_die >= 0)
	{
		philo[i].args = args;
		if (pthread_create(&philo[i].thread, NULL, tf_philo_actions, &philo[i]))
			return (FAIL);
	//	printf("thread created\n");
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
 */

int	init_mutex_fork(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		//philo[i].fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		//if (philo[i].fork_left == NULL)
		//	return (FAIL);
		if (pthread_mutex_init(&philo[i].fork_left, NULL) != 0)
			return (FAIL);
		printf("mutex initialized\n");
		i++;
	}
	i = 0;
	while (i < args->nb_philos)
	{
		if (i == args->nb_philos - 1)// if its the last fork
			philo[i].fork_right = philo[0].fork_left;
		else
			philo[i].fork_right = philo[i + 1].fork_left;
		i++;
	}
	if (pthread_mutex_init(&philo->printf, NULL) != 0)
		return (FAIL);
	return (SUCCESS);
}

/*void	init_forks(t_philo *philo, t_args *args, int i)
{
	int	total_philos;

	total_philos = args->nb_philos;
	if (i == 0)// philo->nb == 1
	{
		philo[i].left_fork = i + 1;
		philo[i].right_fork = total_philos;
	}
	else if (i == total_philos - 1)// philo->nb == philo->total
	{
		philo[i].left_fork = total_philos;
		philo[i].right_fork = i - 1;
	}
	else
	{
		philo[i].left_fork = i + 1;
		philo[i].right_fork = i;
	}
}*/

void	init_args_dt(t_args *args, char **argv)
{

	args->dt = 1;
	args->nb_philos = ft_atoi(argv[2]);
	args->time_to_die = ft_atoi(argv[3]);
	args->time_to_eat = ft_atoi(argv[4]);
	args->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6])
		args->times_philo_must_eat = ft_atoi(argv[6]);
	else
		args->times_philo_must_eat = 0;
	if (args->nb_philos < 2 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0 ||
		args->times_philo_must_eat < 0)
		return ;
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", args->nb_philos, args->time_to_die, args->time_to_eat, args->time_to_sleep, args->times_philo_must_eat);
// TEST
}
/*{
	int	i;

	i = 0;
	philo[0].dt = 1;
	philo->index = 0;
	philo->nb_philos = ft_atoi(argv[2]);
	philo->position = 0;
	//if ((philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->nb_philos)) == NULL)
	//	return ;
	while (i < philo[0].nb_philos)
	{
		philo[i].position = i + 1;
		init_forks(philo, i);
		//printf("nb[%d] = %d\nleft_fork = %d\nright_fork = %d\n", i, args->nb_philos, philo->left_fork[i], philo->right_fork[i]);
		i++;
	}
	philo->time_to_die = ft_atoi(argv[3]);
	philo->time_to_eat = ft_atoi(argv[4]);
	philo->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6])
		philo->times_philo_must_eat = ft_atoi(argv[6]);
	else
		philo->times_philo_must_eat = 0;
	if (philo->nb_philos < 2 || philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0 || philo->times_philo_must_eat < 0)
		return ;
// TEST
//	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", args->nb_philos, args->time_to_die, args->time_to_eat, args->time_to_sleep, args->times_philo_must_eat);
// TEST
}*/

void	init_philo(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		philo[i].position = i + 1;

		philo[i].start_time = get_time();
		philo[i].one_philo_died = 0;
		philo[i].last_meal_time = get_time();
//		init_forks(philo, args, i);
//		printf("		nb[%d] = %d\nleft_fork = %d\nright_fork = %d\n", i, philo[i].position, philo[i].left_fork, philo[i].right_fork);
		i++;
	}
// TEST
	printf("START_TIME = %ld\n", philo->start_time);
// TEST
}

void	init_args(t_args *args, char **argv)
{
	args->dt = 0;
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->times_philo_must_eat = ft_atoi(argv[5]);
	else
		args->times_philo_must_eat = 0;
	if (args->nb_philos < 2 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0 ||
		args->times_philo_must_eat < 0)
		return ;
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", args->nb_philos, args->time_to_die, args->time_to_eat, args->time_to_sleep, args->times_philo_must_eat);
// TEST
}

/*void	init_args(t_philo *philo, t_args *args, char **argv)
{
	t_forks	forks;
	int	i;
	i = 1;
	//if ((philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]))) == NULL)
	//	return ;
	philo[0].dt = 0;
	philo[0].start_time = get_time();
	philo[0].nb_philos = ft_atoi(argv[1]);
	philo[0].index = 1;
	philo[0].time_to_die = ft_atoi(argv[2]);
	philo[0].time_to_eat = ft_atoi(argv[3]);
	philo[0].time_to_sleep = ft_atoi(argv[4]);
	while (i <= philo[0].nb_philos)
	{
		philo[i].position = i;
		init_forks(philo, &forks, i);
		printf("		nb[%d] = %d\nleft_fork = %d\nright_fork = %d\n", i, philo[i].position, philo[i].left_fork, philo[i].right_fork);
		i++;
	}
	if (argv[5])
		philo[0].times_philo_must_eat = ft_atoi(argv[5]);
	else
		philo[0].times_philo_must_eat = 0;
	if (philo[0].nb_philos < 2 || philo[0].time_to_die < 0 ||
		philo[0].time_to_eat < 0 || philo[0].time_to_sleep < 0 ||
		philo[0].times_philo_must_eat < 0)
		return ;
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", philo[0].nb_philos, philo[0].time_to_die, philo[0].time_to_eat, philo[0].time_to_sleep, philo[0].times_philo_must_eat);
	printf("START_TIME = %ld\n", philo[0].start_time);
// TEST
}*/
