/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 09:40:35 by whoami            #+#    #+#             */
/*   Updated: 2021/07/24 23:10:01 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_status_header()
{
	printf("┌───────────────┬─────────┬─────────────────────────┐\n");
	printf("│ Time          │ Philo   │ Event                   │\n");
	printf("├───────────────┼─────────┼─────────────────────────┤\n");
}

void	print_status_header_optional()
{
	printf("┌───────────────┬─────────┬─────────────────────────┬───────────┐");
	printf("\n");
	printf("│ Time          │ Philo   │ Event                   │ Diff Time │");
	printf("\n");
	printf("├───────────────┼─────────┼─────────────────────────┼───────────┤");
	printf("\n");
}

void	print_status(t_philo *philo, t_const_data *const_data,  char *action)
{
	int	diff_time;

	diff_time = 0;
	pthread_mutex_lock(&const_data->print_action);
	if (const_data->one_philo_died == FALSE)
	{
		//pthread_mutex_lock(&const_data->print_action);
		printf("│ %ld │ ",  get_current_time());;
		printf("philo %d │ %s%s│", philo->position, action, COLOR_RESET);
		if (const_data->diff_time_arg == TRUE)
		{
			diff_time = get_current_time() - const_data->start_time;
			if (diff_time < 10)
				printf(" %d         │", diff_time);
			else if (diff_time < 100)
				printf(" %d        │", diff_time);
			else if (diff_time < 1000)
				printf(" %d       │", diff_time);
			else
				printf(" %d      │", diff_time);
		}
		printf("\n");
		//pthread_mutex_unlock(&const_data->print_action);
	}
	pthread_mutex_unlock(&const_data->print_action);
}
