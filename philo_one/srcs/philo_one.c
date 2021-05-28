/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/28 04:29:20 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_status(t_philo *philo,  char *action)
{
	unsigned int diff_time;

	printf("%ld philo(%d) %s", get_time(), philo[philo[0].index].position, action);
	if (philo[0].dt == 1)
	{
		diff_time = get_diff_time(philo[0].start_time);
		printf(" | ms from last status = %d", diff_time);
	}
	printf("\n");
}

/*
 *
 */

void	philo_takes_fork(t_philo *philo)//, t_args *args)
{
	pthread_mutex_lock(&philo[philo[philo[0].index].left_fork].forks);
	print_status(philo, "has taken a fork (left fork)");

	pthread_mutex_lock(&philo[philo[philo[0].index].left_fork].forks);
	print_status(philo, "has taken a fork (right fork)");

	printf("left_fork = %d ------ ", philo[philo[0].index].left_fork);
	printf("right_fork = %d\n", philo[philo[0].index].right_fork);

	pthread_mutex_unlock(&philo[philo[philo[0].index].left_fork].forks);
	pthread_mutex_unlock(&philo[philo[philo[0].index].left_fork].forks);
}

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */

void	check_if_dead(t_philo *philo)//, t_args *args)
{
	unsigned long diff_time;

	diff_time = get_diff_time(philo[0].start_time);

	printf("TIME TO DIE = %ld\n", (unsigned long)philo[0].time_to_die);
	printf("start time = %ld\n", philo[0].start_time);
	printf("diff time = %d\n\n", (int)diff_time);

	if (diff_time > (unsigned long)philo[0].time_to_die)
	{
		print_status(philo, "died");
		philo[0].time_to_die = -1;
	}
}

/*
 * Funtion called by the pthread_create function.
 * void *actions = &philo[i] whenre i > 0 && i < philo->nb.
 *
 * --------
 * philo eating → can't think or sleep.
 * philo sleeping → can't eat or think.
 * philo thinking → can't eat or sleep.
 *
 * Right after a philo stops eating, s/he puts down her/is fork and go sleep.
 * When a philosopher stops to sleep, s/he starts to think!!!
 */

void	*tf_philo_actions(void *actions)
{
	t_philo	*philo;
//	t_args	*args;

	philo = (t_philo*)actions;
	while (philo[0].time_to_die >= 0)
	{
		check_if_dead(philo);//, args);
		philo_takes_fork(philo);//, args);
		//philo_eat(philo);
		//philo_sleep(philo);
		//philo_think(philo);
	}
	return (NULL);
}
