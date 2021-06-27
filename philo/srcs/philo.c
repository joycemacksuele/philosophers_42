/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/26 22:10:55 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * int usleep(useconds_t microseconds);
 * As usleep take microseconds as it's parameter, and time_to_eat is in
 * milliseconds, conversion need to be done:
 * 1 microsecond = 1 millisecond * 1000
 */

void	philo_eat(t_philo *philo, t_args *args)
{
//	pthread_mutex_lock(&philo->fork_left);
//	pthread_mutex_lock(&philo->fork_right);
	pthread_mutex_lock(&philo->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->fork[philo->right_fork]);

	//pthread_mutex_lock(&philo->print_action);
	print_status(philo, COLOR_BLUE"has taken a fork (left fork)  ");
	print_status(philo, COLOR_CYAN"has taken a fork (right fork) ");
	print_status(philo, COLOR_GREEN"is eating                     ");
	//pthread_mutex_unlock(&philo->print_action);

//	pthread_mutex_lock(&philo->print_action);
//	printf("left_fork = %d ------ ", philo->left_fork);
//	printf("right_fork = %d\n", philo->right_fork);
//	pthread_mutex_unlock(&philo->print_action);
//	printf("time to eat = %d\n", args->time_to_eat * 1000);

	philo->last_meal_time = get_current_time();
	//printf("last_meal_time = %ld\n", philo->last_meal_time);
	//printf("time to eat microsecond = %d\n", args->time_to_eat * 1000);
	usleep(args->time_to_eat * 1000);

	pthread_mutex_unlock(&philo->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->fork[philo->right_fork]);
//	pthread_mutex_unlock(&philo->fork_left);
//	pthread_mutex_unlock(&philo->fork_right);

}

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */

void	check_if_dead(t_philo *philo, t_args *args)// ARRUMAR E FAZER PHILO MORRER
{
	//unsigned long diff_time;
	unsigned long current_time;
	bool chech_if_last_meal_time_bigger_than_time_to_die;
//	diff_time = get_diff_time(philo->start_time);

	current_time = get_current_time();
	chech_if_last_meal_time_bigger_than_time_to_die = (current_time - philo->last_meal_time >= (unsigned long)args->time_to_die);
/*	printf("  start time = %ld\n", philo->start_time);
	printf("  current time = %ld\n", current_time);
	printf("  last meal time = %ld\n", philo->last_meal_time);
	printf("  current time - last meal time = %ld\n", current_time - philo->last_meal_time);
	printf("TIME TO DIE = %d\n", args->time_to_die);*/
	usleep(args->time_to_die * ONE_MS);
	if (chech_if_last_meal_time_bigger_than_time_to_die)
//	if (current_time - philo->last_meal_time >= (unsigned long)args->time_to_die)// 10ms a mais e permitido nao como esta agora
	{
		print_status(philo, COLOR_RED"died"COLOR_RESET);
		philo->one_philo_died = -1;
	}
}

/*
 * Funtion called by the pthread_create function.
 * void *actions = &philo[i] where i > 0 && i < philo->nb.
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

	philo = (t_philo*)actions;
	args = philo->args;
	//printf("TIME TO DIE = %d\n", args->time_to_die);

	while (philo->one_philo_died == 0)
	{
		philo_eat(philo, args);
		//philo_sleep(philo);
		//philo_think(philo);
	}
	return (NULL);
}
