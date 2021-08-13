/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/11 22:34:09 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <sys/wait.h>
# include <signal.h>

/*
 * initialization of struct/mutex/pthreads
 */
int				init_data(t_const_data *const_data, char **argv);
int				init_data_diff_time(t_const_data *const_data, char **argv);
void			init_philo(t_philo *philo, t_const_data *const_data);
void			init_semaphores(t_const_data *const_data);
int				init_process_philos(t_philo *philo, t_const_data *const_data);

/*
 * Philosophers actions
 */
void			child_process(void *philos);
//void			child_process(t_philo *philo, t_const_data *const_data);
void			check_if_all_ate(t_philo *philo, t_const_data *const_data);
void			*check_death(void *philos);
void			terminate_process(t_philo *philo, t_const_data *const_data);
void			terminate_semaphores(t_const_data *const_data);

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
