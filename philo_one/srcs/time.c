/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:22:32 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/08 03:23:12 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned int	get_diff_time(unsigned int start_time)//later can be changed to phile->start_time
{
	struct timeval	time;
	int				ms_time;

	usleep(10000);
	gettimeofday(&time, NULL);
	ms_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// TEST
	printf("SIZEOF(UNSIGNED INT) = %zu\n", sizeof(unsigned int));
	printf("SIZEOF(UNSIGNED LONG) = %zu\n", sizeof(unsigned long));
	printf("\n--------------\n");
	printf("start ms time = %d ms\n", start_time);
	printf("current ms time = %d ms\n", ms_time);
	printf("diff from start time and current time = %d ms\n", ms_time - start_time);

// TEST
	return (ms_time - start_time);
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

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
// TEST
	printf("sec = %ld\n", time.tv_sec);
	printf("		-> sec in milli = %ld\n", time.tv_sec * 1000);
	printf("--------------\n");
	printf("sec + micro = %ld\n", (time.tv_sec + time.tv_usec));
	printf("--------------\n");
	printf("micro = %ld\n", time.tv_usec);
	printf("		-> micro in milli = %ld\n", time.tv_usec / 1000);
	printf("--------------\n");
	printf("sec + micro in milli = %ld\n", (time.tv_sec * 1000) + (time.tv_usec / 1000));

	get_diff_time((time.tv_sec * 1000) + (time.tv_usec / 1000));
// TEST
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
