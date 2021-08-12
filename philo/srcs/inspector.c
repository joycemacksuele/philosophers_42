/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:33:05 by whoami            #+#    #+#             */
/*   Updated: 2021/08/07 18:44:29 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dies_print(t_philo *philo, t_const_data *const_data, int i)
{
	pthread_mutex_lock(&const_data->check_death);
	pthread_mutex_lock(&const_data->print_action);
	print_status(&philo[i], const_data, COLOR_RED
		"died                    "COLOR_RESET);
	pthread_mutex_unlock(&const_data->print_action);
	const_data->one_philo_died = TRUE;
	pthread_mutex_unlock(&const_data->check_death);
}

/* try this if someone does not die when s/he should!
 * else if (last_meal_diff_time > const_data->time_to_die
 * 	&& const_data->is_eating == FALSE)
 * 	philo_dies_print(philo, const_data, i);
 */

void	philo_dies(t_philo *philo, t_const_data *const_data, int i)
{
	int	last_meal_diff_time;
	int	last_meal_diff_from_start;

	last_meal_diff_from_start = get_diff_time(const_data->start_time);
	last_meal_diff_time = get_diff_time(philo[i].last_meal_time);
	if (last_meal_diff_from_start > const_data->time_to_die
		&& philo[i].ate == 0)
		philo_dies_print(philo, const_data, i);
	else if (last_meal_diff_time > const_data->time_to_die)
		philo_dies_print(philo, const_data, i);
}

void	check_death(t_philo *philo, t_const_data *const_data)
{
	int	i;

	while (const_data->one_philo_died == FALSE && philo->satisfied == FALSE)
	{
		i = 0;
		while (i < const_data->nb_philos && const_data->one_philo_died == FALSE
			&& philo[i].satisfied == FALSE)
		{
			philo_dies(philo, const_data, i);
			usleep(100);
			i++;
		}
		if (philo->satisfied == TRUE || const_data->one_philo_died == TRUE)
			break ;
	}
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
