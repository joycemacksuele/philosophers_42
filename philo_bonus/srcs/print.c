/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <jfreitas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 09:40:35 by whoami            #+#    #+#             */
/*   Updated: 2021/08/14 20:38:55 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status_header(int finished)
{
	if (finished == 0)
	{
		printf("┌───────────────┬─────────┬─────────────────────────┐\n");
		printf("│ Time          │ Philo   │ Event                   │\n");
		printf("├───────────────┼─────────┼─────────────────────────┤\n");
	}
	else
		printf("└───────────────┴─────────┴─────────────────────────┘\n");
}

void	print_status(t_philo *philo, t_const_data *const_data, char *action)
{
	int	diff_time;

	diff_time = 0;
	if (const_data->one_philo_died == FALSE)
	{
		printf("│ %ld │ ", get_current_time());
		printf("philo %d │ %s%s│", philo->position, action, COLOR_RESET);
		printf("\n");
	}
}
