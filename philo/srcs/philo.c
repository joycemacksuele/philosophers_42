/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/27 22:17:32 by whoami           ###   ########.fr       */
/* ************************************************************************** */

#include "philo_one.h"

void philo_takes_forks(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->fork[philo->left_fork]);
	pthread_mutex_lock(&const_data->fork[philo->right_fork]);

	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_BLUE"has taken left fork     ");
	pthread_mutex_unlock(&const_data->print_action);

	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_CYAN"has taken right fork    ");
	pthread_mutex_unlock(&const_data->print_action);

	/*pthread_mutex_lock(&const_data->print_action);
	printf("philo[%d] -> ", philo->position);
	printf("left_fork = %d ------ ", philo->left_fork);
	printf("right_fork = %d\n", philo->right_fork);
	pthread_mutex_unlock(&const_data->print_action);*/
}

/*
 * int usleep(useconds_t microseconds);
 * As usleep take microseconds as it's parameter, and time_to_eat is in
 * milliseconds, conversion need to be done:
 * 1 microsecond = 1 millisecond * 1000
 */

void	philo_eats(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->check_death);// so it wont eat if its dead
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_GREEN"is eating               ");
	philo->last_meal_time = get_current_time();

	//printf("philo[%d]\n", philo->position);

	pthread_mutex_unlock(&const_data->print_action);

	pthread_mutex_unlock(&const_data->check_death);
	usleep(const_data->time_to_eat * ONE_MS);
	philo->ate = philo->ate + 1;
	//pthread_mutex_lock(&const_data->print_action);
	//printf("philo[%d] left forks!\n", philo->position);
	//pthread_mutex_unlock(&const_data->print_action);
	pthread_mutex_unlock(&const_data->fork[philo->left_fork]);
	pthread_mutex_unlock(&const_data->fork[philo->right_fork]);
}

void	philo_sleeps(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_YELLOW"is sleeping             ");
	pthread_mutex_unlock(&const_data->print_action);
	usleep(const_data->time_to_sleep * ONE_MS);

	//printf("time_to_sleep = %d\n", const_data->time_to_sleep);
}

void	philo_thinks(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_PINK"is thinking             ");
	pthread_mutex_unlock(&const_data->print_action);
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
	t_philo			*philo;
	t_const_data	*const_data;

	philo = (t_philo*)actions;
	const_data = philo->const_data;
	if (philo->position % 2 == 0)// if its even
	{
		//printf("POSITION = %d\n", philo->position);
		usleep(10000);
	}
	while (const_data->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		check_if_all_ate(philo, const_data);
		philo_takes_forks(philo, const_data);
		philo_eats(philo, const_data);
		if (philo->satisfied == TRUE)
			break ;
			//return (0);
		philo_sleeps(philo, const_data);
		philo_thinks(philo, const_data);
		//usleep(30000);
	}
	return (NULL);
}
