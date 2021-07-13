/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:33:05 by whoami            #+#    #+#             */
/*   Updated: 2021/07/12 22:25:40 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */

void	check_if_dead(t_philo *philo, t_args *args, t_checker *checker)// ARRUMAR E FAZER PHILO MORRER
{
	int	i;
//	bool chech_death;

	i = 0;
//	chech_death = (get_diff_time(philo[i].last_meal_time) <= (unsigned long)args->time_to_die);
//	printf("  start time = %ld\n", philo->start_time);
//	printf("  current time = %ld\n", get_current_time());
	printf("\n\nENTERED CHECK OF DEAD\n\n");
	while (i < args->nb_philos && checker->one_philo_died == FALSE)
	//if (checker->one_philo_died == FALSE)
	{
		pthread_mutex_lock(&checker->check_death);
		printf("last meal = %ld\ntime to die = %ld\n", get_diff_time(philo[i].checker.last_meal_time), (unsigned long)args->time_to_die);
		if (get_diff_time(checker->last_meal_time) >= (unsigned long)args->time_to_die)
		{
			print_status(&philo[i], &philo[i].checker, COLOR_RED"died                          "COLOR_RESET);
			philo[i].checker.one_philo_died = TRUE;
		}
		pthread_mutex_unlock(&checker->check_death);
		i++;
	}
//10ms a mais e permitido nao como esta agora
}

/*
 * This funtion will check if all philos had eaten and if so, set the variable
 * satisfied, inside the philo struc, to 1.
 * So it can be used by the tf_philo_actions function to stop it's job if all
 * all philos had already eaten
 */

void	check_if_all_ate(t_args *args, t_checker *checker)
{
	if (args->times_philo_must_eat != FALSE && checker->satisfied == FALSE)
	{
		if (checker->ate >= args->times_philo_must_eat)
		{
			printf("ate = %d\nlast param = %d\n", checker->ate, args->times_philo_must_eat);
			printf("ENTERED LAST PARAM\n");
			checker->satisfied = TRUE;
		}
	}
}
