/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/08 02:58:49 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *						void *(*start_routine) (void *), void *arg);
 */

void	init_pthread_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		pthread_create(&(philo[i].pt), NULL, philo_actions, &(philo[i]));
		i++;
	}

}

/*
 * Initializating a mutex to each fork (which is the "number_of_philosopher"
 * given as input by the user).
 *
 * int	pthread_mutex_init(pthread_mutex_t *mutex,
 *										const pthread_mutexattr_t *mutexattr);
 */

void	init_mutex_fork(t_philo *philo)
{
	int	fork_i;

	fork_i = 0;

	while (fork_i < philo->nb)
	{
		philo[fork_i].fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[fork_i].fork, NULL);
		fork_i++;
	}
}

void	init_args(t_philo *philo, char **argv)
{
	philo->fork = NULL;
	philo->nb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->times_philo_must_eat = ft_atoi(argv[5]);
	else
		philo->times_philo_must_eat = 0;
	if (philo->nb < 2 || philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0 || philo->times_philo_must_eat < 0)
		return ;
// TEST
	printf(">>>> args = %d, %d, %d, %d, %d <<<<\n\n", philo->nb, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, philo->times_philo_must_eat);
// TEST
}
