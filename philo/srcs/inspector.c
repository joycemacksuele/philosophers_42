/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:33:05 by whoami            #+#    #+#             */
/*   Updated: 2021/07/07 21:08:11 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */

void	check_if_dead(t_philo *philo, t_args *args)// ARRUMAR E FAZER PHILO MORRER
{
	unsigned long current_time;
	bool chech_if_last_meal_time_bigger_than_time_to_die;

	current_time = get_current_time();
	chech_if_last_meal_time_bigger_than_time_to_die = (current_time - philo->last_meal_time >= (unsigned long)args->time_to_die);
//	printf("  start time = %ld\n", philo->start_time);
//	printf("  current time = %ld\n", current_time);
//	usleep(args->time_to_die * ONE_MS);
	if (chech_if_last_meal_time_bigger_than_time_to_die)
//	if (current_time - philo->last_meal_time >= (unsigned long)args->time_to_die)// 10ms a mais e permitido nao como esta agora
	{
		print_status(philo, COLOR_RED"died"COLOR_RESET);
		philo->one_philo_died = -1;
	}

}

/*
 * This funtion will check if all philos had eaten and if so, set the variable
 * satisfied, inside the philo struc, to 1.
 * So it can be used by the tf_philo_actions function to stop it's job if all
 * all philos had already eaten
 */

void	check_if_all_ate(t_philo *philos, t_args *args)
{
	if (philos->satisfied == FALSE && philos->ate >= args->times_philo_must_eat)
		philos->satisfied = TRUE;
}
