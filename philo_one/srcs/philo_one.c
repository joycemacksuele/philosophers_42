/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/09 15:31:17 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_status(t_philo *philo,  char *action)
{
	unsigned int diff_time;

	if (philo->one_philo_died == 0)
	{
		printf("| %ld | philo %d | %s \n", get_time(), philo->position, action);
		if (philo->args->dt == 1)
		{
			diff_time = get_diff_time(philo->start_time);
			printf(" ms from last status = %d\n", diff_time);
		}
	}
}

/*
 *
 */

void	philo_eats(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&philo->fork_left);
	pthread_mutex_lock(&philo->fork_right);
	pthread_mutex_lock(&philo->printf);
	print_status(philo, "has taken a fork (left fork)      |");
	print_status(philo, "has taken a fork (right fork)     |");
	print_status(philo, "is eating                         |");

//	printf("left_fork = %d ------ ", *philo->fork_left);
//	printf("right_fork = %d\n", &philo->fork_right);

	philo->last_meal_time = get_time();
	usleep(args->time_to_eat * ONE_MS);// here the philo is eating time_to_eat milliseconds
	pthread_mutex_unlock(&philo->printf);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(&philo->fork_right);

}

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */

void	check_if_dead(t_philo *philo, t_args *args)
{
	//unsigned long diff_time;
	unsigned long current_time;
//	diff_time = get_diff_time(philo->start_time);

	current_time = get_time();
/*	printf("  start time = %ld\n", philo->start_time);
	printf("  current time = %ld\n", current_time);
	printf("  last meal time = %ld\n", philo->last_meal_time);
	printf("  current time - last meal time = %ld\n", current_time - philo->last_meal_time);
	printf("TIME TO DIE = %d\n", args->time_to_die);*/
	usleep(args->time_to_die * ONE_MS);
	if (current_time - philo->last_meal_time >= (unsigned long)args->time_to_die)// 10ms a mais e permitido nao como esta agora
	{
		print_status(philo, COLOR_RED"died"COLOR_RESET);
		philo->one_philo_died = -1;
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
	t_args	*args;
	int		i;

	i = 0;
	philo = (t_philo*)actions;
	args = philo->args;
	//printf("TIME TO DIE = %d\n", args->time_to_die);

	while (philo->one_philo_died == 0)
	{
		check_if_dead(philo, args);
		philo_eats(philo, args);
		//philo_eat(philo);
		//philo_sleep(philo);
		//philo_think(philo);
		i++;
	}
	return (NULL);
}
