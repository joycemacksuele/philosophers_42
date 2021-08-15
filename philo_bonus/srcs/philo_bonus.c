/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 00:10:01 by whoami            #+#    #+#             */
/*   Updated: 2021/08/14 21:32:05 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* For testing purposes:
 * sem_wait(&const_data->print_action);
 * printf("philo[%d] -> ", philo->position);
 * printf("left_fork = %d ------ ", philo->left_fork);
 * printf("right_fork = %d\n", philo->right_fork);
 * sem_post(&const_data->print_action);
 *
 * int sem_wait(sem_t *sem);
 * int sem_post(sem_t *sem);
 */

void	philo_takes_forks(t_philo *philo, t_const_data *const_data)
{
	sem_wait(const_data->fork);
	sem_wait(const_data->fork);
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_BLUE"has taken a fork        ");
	sem_post(const_data->print_action);
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_BLUE"has taken a fork        ");
	sem_post(const_data->print_action);
}

/*
 * int usleep(useconds_t microseconds);
 * As usleep take microseconds as it's parameter, and time_to_eat is in
 * milliseconds, conversion need to be done:
 * 1 microsecond = 1 millisecond * 1000
 *
 * sem_wait(&const_data->check_death); -> so it wont eat if
 * its dead
 *
 * usleep(const_data->time_to_eat * ONE_MS); and
 * usleep(const_data->time_to_sleep * ONE_MS); are other options but it did
 * not work well.
 */

void	philo_eats(t_philo *philo, t_const_data *const_data)
{
	sem_wait(const_data->check_death);
	philo->ate = philo->ate + 1;
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_GREEN"is eating               ");
	sem_post(const_data->print_action);
	sem_post(const_data->check_death);
	philo->last_meal_time = get_current_time();
	while ((int)(get_current_time() - philo->last_meal_time) <
		const_data->time_to_eat)
		usleep(ONE_MS);
	sem_post(const_data->fork);
	sem_post(const_data->fork);
}

void	philo_sleeps(t_philo *philo, t_const_data *const_data)
{
	unsigned int	current_time;

	current_time = get_current_time();
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_YELLOW"is sleeping             ");
	sem_post(const_data->print_action);
	while ((int)(get_current_time() - current_time) < const_data->time_to_sleep)
		usleep(ONE_MS);
}

void	philo_thinks(t_philo *philo, t_const_data *const_data)
{
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_PINK"is thinking             ");
	sem_post(const_data->print_action);
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

void	child_process(t_philo *philo, t_const_data *const_data)
{
	pthread_t	death_check;

	pthread_create(&death_check, NULL, check_death, philo);
	pthread_detach(death_check);
	if (philo->position % 2 == 0)
		usleep(ONE_MS);
	while (const_data->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		check_if_all_ate(philo, const_data);
		philo_takes_forks(philo, const_data);
		if (philo->satisfied == TRUE)
			exit(TRUE);
		philo_eats(philo, const_data);
		if (const_data->one_philo_died == TRUE)
			exit(FALSE);
		philo_sleeps(philo, const_data);
		philo_thinks(philo, const_data);
	}
	exit(TRUE);
}
