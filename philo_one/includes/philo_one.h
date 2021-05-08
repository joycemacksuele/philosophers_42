/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/08 03:23:20 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_philo
{
	pthread_t		pt;
	pthread_mutex_t	*fork;
	unsigned long	start_time;
	int				nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
}					t_philo;

/*
 * initialization of struc/mutex/pthreads
 */
void	init_args(t_philo *philo, char **argv);
void	init_mutex_fork(t_philo *philo);
void	init_pthread_philos(t_philo *philo);

/*
 * Philosophers actios
 */
void	*philo_actions(void *actions);
void	philo_eat(t_philo *philo);

/*
 * time
 */
unsigned long	get_time(void);

/*
 * UTILS
 */
int	ft_atoi(char const *str);

/*
 * Errors
 */


#endif
