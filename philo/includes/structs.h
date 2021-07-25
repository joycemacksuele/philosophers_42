/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/07/24 22:32:07 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./philo_one.h"
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
# include <stdbool.h>

# define FAIL -1
# define SUCCESS 0

# define TRUE 1
# define FALSE 0

# define ONE_MS 1000

# define COLOR_RED		"\x1b[31m"// dead and all philos has eaten
# define COLOR_BLUE		"\x1b[34m"// took leftt fork
# define COLOR_CYAN		"\x1b[36m"// took right fork
# define COLOR_GREEN	"\x1b[32m"// eating
# define COLOR_YELLOW	"\x1b[33m"// sleeping
# define COLOR_PINK		"\x1b[35m"// thinking
# define COLOR_RESET	"\x1b[0m"

/*typedef struct s_checker
{
	pthread_mutex_t	print_action;
	pthread_mutex_t	check_death;
	//int				one_philo_died;
//	int				satisfied;
}					t_checker;*/

typedef struct s_const_data
{
	int				diff_time_arg;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	pthread_mutex_t	print_action;
	pthread_mutex_t	check_death;
	pthread_mutex_t	fork[200];
	int				one_philo_died;
	int				satisfied;
	unsigned long	start_time;
}					t_const_data;

typedef struct s_philo
{
	pthread_t		thread;
	//pthread_mutex_t	fork[200];
	//pthread_mutex_t	print_action[200];
	int				left_fork;
	int				right_fork;
	int				position;
	int				ate;
	unsigned long	last_meal_time;
	//int				satisfied;
	t_const_data	*const_data;
}					t_philo;

#endif