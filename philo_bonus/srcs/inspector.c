/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:33:05 by whoami            #+#    #+#             */
/*   Updated: 2021/08/11 22:29:59 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_dies_print(t_philo *philo, t_const_data *const_data)
{
	sem_wait(const_data->check_death);
	sem_wait(const_data->print_action);
	print_status(philo, const_data, COLOR_RED
		"died                    "COLOR_RESET);
	sem_post(const_data->print_action);
	sem_post(const_data->check_death);
	const_data->one_philo_died = TRUE;
	exit(FAIL);
}

void	philo_dies(t_philo *philo, t_const_data *const_data)
{
	int	last_meal_diff_time;
	int	last_meal_diff_from_start;

	last_meal_diff_from_start = get_diff_time(const_data->start_time);
	last_meal_diff_time = get_diff_time(philo->last_meal_time);
	if (last_meal_diff_from_start > const_data->time_to_die
		&& philo->ate == 0)
		philo_dies_print(philo, const_data);
	if (last_meal_diff_time > const_data->time_to_die)
		philo_dies_print(philo, const_data);
}

void	*check_death(void *philos)
{
	t_philo			*philo;
	t_const_data	*const_data;

	philo = (t_philo *)philos;
	const_data = philo->const_data;
	while (const_data->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		philo_dies(philo, const_data);
		if (philo->satisfied == TRUE || const_data->one_philo_died == TRUE)
			exit(FAIL);
		usleep(ONE_MS);
	}
	return (NULL);
}

/*
 * This funtion will check if all philos had eaten and if so, set the variable
 * satisfied, inside the philo struc, to 1.
 * So it can be used by the tf_philo_actions function to stop it's job if all
 * all philos had already eaten
 */

void	check_if_all_ate(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	if (const_data->times_philo_must_eat == FALSE)
		return ;
	while (i < const_data->nb_philos)
	{
		if (philo[i].ate >= const_data->times_philo_must_eat)
			philo[i].satisfied = TRUE;
		i++;
	}
}
