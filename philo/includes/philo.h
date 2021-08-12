/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/07 19:58:29 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./structs.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

/*
 * initialization of struct/mutex/pthreads
 */
int				init_data(t_const_data *const_data, char **argv);
int				init_data_diff_time(t_const_data *const_data, char **argv);
void			init_philo(t_philo *philo, t_const_data *const_data);
int				init_mutexes(t_const_data *const_data);
int				init_pthread_philos(t_philo *philo, t_const_data *const_data);

/*
 * Philosophers actions
 */
void			*tf_philo_actions(void *actions);
void			check_if_all_ate(t_philo *philo, t_const_data *const_data);
void			check_death(t_philo *philo, t_const_data *const_data);
void			terminate_threads(t_philo *philo, t_const_data *const_data);
void			terminate_mutexes(t_const_data *const_data);

/*
 * Printing on stdout
 */
void			print_status_header(int finished);
void			print_status_header_optional(int finished);
void			print_status(t_philo *philos, t_const_data *const_data,
					char *action);

/*
 * time
 */
unsigned long	get_current_time(void);
int				get_diff_time(unsigned long start_time);

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
