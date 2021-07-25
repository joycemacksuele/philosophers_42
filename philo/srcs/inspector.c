/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:33:05 by whoami            #+#    #+#             */
/*   Updated: 2021/07/24 23:04:15 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 * It's will update philo[0].time_to_die to -1 in case a philosofer is
 * considered dead
 */
void	check_death(t_philo *philo, t_const_data *const_data)
{
	int				i;
	unsigned long	last_meal_diff_time;

	i = 0;
	last_meal_diff_time = 0;
	//printf("\n-----\nENTERED CHECK_DEATH\n");
	while (const_data->satisfied == FALSE)
	{
		i = 0;
		while (i < const_data->nb_philos && const_data->one_philo_died == FALSE)
		{
			last_meal_diff_time = get_diff_time(philo[i].last_meal_time);
			if (last_meal_diff_time >= (unsigned long)const_data->time_to_die)
			{
				pthread_mutex_lock(&const_data->check_death);
				//pthread_mutex_lock(&const_data->print_action);
				print_status(&philo[i], const_data, COLOR_RED
										"died                    "COLOR_RESET);
				//pthread_mutex_unlock(&const_data->print_action);
				const_data->one_philo_died = TRUE;

				pthread_mutex_unlock(&const_data->check_death);
			}
			i++;
		}
		if (const_data->one_philo_died == TRUE)
		{
			//printf("last meal diff time = %ld\ntime to die = %ld\n----\n", get_diff_time(philo[i].last_meal_time), (unsigned long)const_data->time_to_die);
			//printf("i = %d\n", i);
			break ;
		}
		check_if_all_ate(philo, const_data);
	//	usleep(1000);
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
	while (i < const_data->nb_philos && philo[i].ate >= const_data->times_philo_must_eat)
	{
		printf("ate = %d - last param = %d - ", philo[i].ate, const_data->times_philo_must_eat);
		printf("philo[%d]\n", philo[i].position);
		i++;
	}
	//{
	if (i == const_data->nb_philos)
		const_data->satisfied = TRUE;
		//{
		//}
		//i++;
//	}
}

/*void	check_if_all_ate(t_philo *philo, t_const_data *const_data)//, t_checker *checker)
{
	int	i;

	i = 0;
	if (const_data->times_philo_must_eat == FALSE)
		return ;
	while (i < const_data->nb_philos)
	{
		if (philo->ate >= const_data->times_philo_must_eat)
		{
			//printf("ate = %d - last param = %d - ", philo[i].ate, const_data->times_philo_must_eat);
			//printf("philo[%d]\n", philo[i].position);
			philo->satisfied = TRUE;
		}
		i++;
	}
}*/
