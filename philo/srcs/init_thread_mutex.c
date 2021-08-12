/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/07 19:25:27 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *						void *(*start_routine) (void *), void *arg);
 *
 *
 *	Creating the same amount of the "number_of_philosopher" input, of threads
 *	on the program  and calling the tf_philo_actions (tf = thread functions),
 *	whithe the index of the structure as it's only paramenter.
 *
 * pthread_detach(philo[i].thread); is another option to stop the threads but
 * it's faster than the pthread_join so it did not work on this program.
 *
 * philo[i].last_meal_time = get_current_time();//add it to see what changes
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
		i++;
	}
	check_death(philo, const_data);
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

int	init_mutexes(t_const_data *const_data)
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
		i++;
	}
	return (SUCCESS);
}
