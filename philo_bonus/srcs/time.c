/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:22:32 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/07 18:47:10 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_diff_time(unsigned long past_time)
{
	unsigned long	current_time_ms;

	current_time_ms = get_current_time();
	return (current_time_ms - past_time);
}

/*
 * The gettimeofday() function gets the system’s clock time.
 * The current time is expressed in elapsed seconds and microseconds since
 * 00:00:00, January 1, 1970 (Unix Epoch).
 *
 *
 * int	gettimeofday(struct timeval *tv, struct timezone *tz);
 *
 * The tv argument is a struct timeval (as specified in <sys/time.h>):
 *		struct timeval {
 *			time_t      tv_sec;    (number of seconds since the epoch)
 *			suseconds_t tv_usec;   (additional microseconds (10^3) after number
 *									of seconds calculation since the epoch)
 *		};
 *
 * OBS.: time_t = long integer
 *
 * OBS.: 1 second = 1000 milliseconds ("milli" is the prefix for 10^3)
 *		 1 second = 1000000 microseconds ("micro" is the prefix for 10^6)
 *
 * @return:
 *		 tv_sec in milliseconds + tv_usec in milliseconds
 * OBS.: 1 millisecond = 1 second * 1000
 *		 1 millisecond = 1 microsecond / 1000
 */

unsigned long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
