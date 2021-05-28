/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/28 04:04:08 by jfreitas         ###   ########.fr       */
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

int	init_pthread_philos(t_philo *philo)//, t_args *args)
{
//	int	i;

//	i = 1;
	printf("INDEX = %d\n", philo[0].index);
	printf("NB TOTAL PHILOS = %d\n", philo[0].nb_philos);
	while (philo[0].index < philo[0].nb_philos)
	{
		if (pthread_create(&philo[philo[0].index].thread, NULL,
			tf_philo_actions, philo) != 0)
			return (FAIL);
		printf("thread created\n");
	//	i++;
		philo[0].index++;
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

void	init_mutex_fork(t_philo *philo)//, t_args *args)// have yo initialize SECOND FORK
{
	int	i;

	i = 1;
//	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
//		philo->nb_philos);
//	if (philo->forks == NULL)
//		return ;
	while (i <= philo[0].nb_philos)
	{
		pthread_mutex_init(&philo[i].forks, NULL);
		printf("mutex initialized\n");
		i++;
	}
}

void	init_forks(t_philo *philo, int i)
{
	int	total;

	total = philo[0].nb_philos;
	if (i == 1)// philo->nb == 1
	{
		philo[i].left_fork = i;
		philo[i].right_fork = philo[0].nb_philos;

	}
	else if (i == philo[0].nb_philos)// philo->nb == philo->total
	{
		philo[i].left_fork = philo[0].nb_philos;
		philo[i].right_fork = i - 1;
	}
	else
	{
		philo[i].left_fork = i;
		philo[i].right_fork = i - 1;
	}
}

void	init_args_dt(t_philo *philo, char **argv)
{
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
}

void	init_args(t_philo *philo, char **argv)
{
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
		init_forks(philo, i);
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
}
