/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 00:10:01 by whoami            #+#    #+#             */
/*   Updated: 2021/08/07 18:44:38 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* For testing purposes:
 * pthread_mutex_lock(&const_data->print_action);
 * printf("philo[%d] -> ", philo->position);
 * printf("left_fork = %d ------ ", philo->left_fork);
 * printf("right_fork = %d\n", philo->right_fork);
 * pthread_mutex_unlock(&const_data->print_action);
 */

void	philo_takes_forks(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->fork[philo->left_fork]);
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_BLUE"has taken left fork     ");
	pthread_mutex_unlock(&const_data->print_action);
	if (philo->right_fork == 0)
		return ;
	pthread_mutex_lock(&const_data->fork[philo->right_fork]);
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_CYAN"has taken right fork    ");
	pthread_mutex_unlock(&const_data->print_action);
}

/*
 * int usleep(useconds_t microseconds);
 * As usleep take microseconds as it's parameter, and time_to_eat is in
 * milliseconds, conversion need to be done:
 * 1 microsecond = 1 millisecond * 1000
 *
 * pthread_mutex_lock(&const_data->check_death); -> so it wont eat if its dead
 *
 * usleep(const_data->time_to_eat * ONE_MS); and
 * usleep(const_data->time_to_sleep * ONE_MS); are other options but it did
 * not work well.
 */

void	philo_eats(t_philo *philo, t_const_data *const_data)
{
	pthread_mutex_lock(&const_data->check_death);
	philo->ate = philo->ate + 1;
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_GREEN"is eating               ");
	pthread_mutex_unlock(&const_data->print_action);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&const_data->check_death);
	while ((int)(get_current_time() - philo->last_meal_time) <
		const_data->time_to_eat)
		usleep(ONE_MS);
	pthread_mutex_unlock(&const_data->fork[philo->left_fork]);
	pthread_mutex_unlock(&const_data->fork[philo->right_fork]);
}

void	philo_sleeps(t_philo *philo, t_const_data *const_data)
{
	unsigned int	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&const_data->print_action);
	print_status(philo, const_data, COLOR_YELLOW"is sleeping             ");
	pthread_mutex_unlock(&const_data->print_action);
	while ((int)(get_current_time() - current_time) < const_data->time_to_sleep)
		usleep(ONE_MS);
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
 * When a philosopher stops to sleep, s/he starts to think.
 *
 * The first if statement with  the usleep,  is to give some time for the
 * odd philos to grab forks and eat otherwise they never get the chance if the
 * time_to_die is close to the time_to_eat + time_to_sleep and someone dies.
 */

void	*tf_philo_actions(void *actions)
{
	t_philo			*philo;
	t_const_data	*const_data;

	philo = (t_philo *)actions;
	const_data = philo->const_data;
	if (philo->position % 2 == 0)
		usleep(ONE_MS);
	while (const_data->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		check_if_all_ate(philo, const_data);
		philo_takes_forks(philo, const_data);
		if (philo->right_fork == 0 || philo->satisfied == TRUE)
			return (NULL);
		philo_eats(philo, const_data);
		if (const_data->one_philo_died == TRUE)
			break ;
		philo_sleeps(philo, const_data);
		philo_thinks(philo, const_data);
	}
	return (NULL);
}
