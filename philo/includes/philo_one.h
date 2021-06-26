/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/25 23:29:20 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "./structs.h"
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
# include <stdbool.h> //defines bool as an alias for C99 _Bool

/*
 * initialization of struct/mutex/pthreads
 */
int				init_args(t_args *args, char **argv);
int				init_args_diff_time(t_args *args, char **argv);
void			init_philo(t_philo *philo, t_args *args);
int				init_mutex_fork(t_philo *philo, t_args *args);
int				init_pthread_philos(t_philo *philo, t_args *args);

/*
 * Philosophers actions
 */
void			*tf_philo_actions(void *actions);
void			philo_eat(t_philo *philo, t_args *args);
void			philo_think(t_philo *philo);
void			philo_spleep(t_philo *philo);

/*
 * Printing on stdout
 */
void			print_status_header(pthread_mutex_t print_action);
void			print_status(t_philo *philo,  char *action);

/*
 * time
 */
unsigned long	get_current_time(void);
unsigned long	get_diff_time(unsigned long start_time);

/*
 * UTILS
 */

/*
 * functions copied from libft
 */
int				ft_atoi(char const *str);
int				ft_strcmp(char const *s1, char const *s2);

/*
 * Errors
 */
void			error_msg(char *err_msg, int args_accepted);

#endif
