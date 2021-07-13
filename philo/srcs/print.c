/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 09:40:35 by whoami            #+#    #+#             */
/*   Updated: 2021/07/12 21:44:52 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_status_header(pthread_mutex_t print_action)//apagar param
{
	(void)print_action;
	printf("┌---------------------------------------------------------┐\n");
	printf("| Time          | Philo   | Event                         |\n");
	printf("|---------------|---------|-------------------------------|\n");
}

void	print_status(t_philo *philo, t_checker *checker, char *action)//AINDA ESTA TABGLED O OUTPPUT com mais de 1 philo thred.. PRECISA de arrumar/mais MUTEX?
{
	//unsigned int	diff_time;
//	unsigned long	current_time;

	if (checker->one_philo_died == 0)
	{
		//pthread_mutex_lock(&philo->print_action);
		//printf("start time = %ld\n", philo->start_time);
		//printf("current time = %ld\n", get_current_time());
		printf("| %ld | ",  get_current_time());// - philo->start_time);
		printf("philo %d | %s%s|", philo->position, action, COLOR_RESET);
		if (philo->args.diff_time == 1)
		{
		//	diff_time = get_diff_time(philo->start_time);
			printf(" ms from last status = ");
			printf("%ld", get_current_time() - philo->start_time);
		}
		printf("\n");
		//pthread_mutex_unlock(&philo->print_action);
	}
}
