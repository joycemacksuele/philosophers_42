/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/14 20:39:21 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./philo_bonus.h"
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

typedef struct s_const_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	unsigned long	start_time;
	unsigned long	time_after_fork;
	int				one_philo_died;
	sem_t			*print_action;
	sem_t			*check_death;
	sem_t			*fork;
	int				one_time;
}					t_const_data;

typedef struct s_philo
{
	pid_t			process;
	int				position;
	int				ate;
	unsigned long	last_meal_time;
	int				satisfied;
	t_const_data	*const_data;
}					t_philo;

#endif
