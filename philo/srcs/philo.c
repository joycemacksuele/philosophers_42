/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/07 21:31:21 by whoami           ###   ########.fr       */
/* ************************************************************************** */

#include "philo_one.h"

void philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->print_action);
	print_status(philo, COLOR_BLUE"has taken a fork (left fork)  ");
	print_status(philo, COLOR_CYAN"has taken a fork (right fork) ");
	pthread_mutex_unlock(&philo->print_action);
}

/*
 * int usleep(useconds_t microseconds);
 * As usleep take microseconds as it's parameter, and time_to_eat is in
 * milliseconds, conversion need to be done:
 * 1 microsecond = 1 millisecond * 1000
 */

void	philo_eats(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&philo->print_action);
	print_status(philo, COLOR_GREEN"is eating                     ");
	pthread_mutex_unlock(&philo->print_action);

//	printf("left_fork = %d ------ ", philo->left_fork);
//	printf("right_fork = %d\n", philo->right_fork);

	//pthread_mutex_lock(&philo->check_death);

	philo->last_meal_time = get_current_time();

	philo->ate = philo->ate + 1;
	//pthread_mutex_unlock(&philo->check_death);// so it wont eat if its dead

	usleep(args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->fork[philo->right_fork]);
}

void	philo_sleeps(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&philo->print_action);
	print_status(philo, COLOR_YELLOW"is sleeping                   ");
	pthread_mutex_unlock(&philo->print_action);
	usleep(args->time_to_sleep * ONE_MS);
}

void	philo_thinks(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_action);
	print_status(philo, COLOR_PINK"is thinking                   ");
	pthread_mutex_unlock(&philo->print_action);
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
	while (philo->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		philo_takes_forks(philo);
		philo_eats(philo, args);
		philo_sleeps(philo, args);
		philo_thinks(philo);
		check_if_all_ate(philo, args);
	}
	return (NULL);
}
