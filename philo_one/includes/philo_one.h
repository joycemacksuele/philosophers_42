/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:13:33 by jfreitas          #+#    #+#             */
/*   Updated: 2021/06/09 15:18:01 by jfreitas         ###   ########.fr       */
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

# define FAIL -1
# define SUCCESS 0

# define ONE_MS 1000

# define COLOR_RED		"\x1b[31m"// dead and all philos has eaten
# define COLOR_YELLOW	"\x1b[33m"// eating
# define COLOR_GREEN	"\x1b[32m"// sleeping
# define COLOR_CYAN		"\x1b[36m"// thinking

# define COLOR_RESET	"\x1b[0m"

typedef struct s_args
{
	int				dt;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
}					t_args;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	printf;
	unsigned long	start_time;
	unsigned long	last_meal_time;
	int				position;
	int				one_philo_died;
	int				philos_are_satisfied;
	t_args			*args;
}					t_philo;


/*
 * initialization of struc/mutex/pthreads
 */
void			init_args(t_args *args, char **argv);
void			init_philo(t_philo *philo, t_args *args);
void			init_args_dt(t_args *args, char **argv);
int				init_mutex_fork(t_philo *philo, t_args *args);
int				init_pthread_philos(t_philo *philo, t_args *args);

/*
 * Philosophers actios
 */
void			*tf_philo_actions(void *actions);
void			philo_eat(t_philo *philo);

/*
 * time
 */
unsigned long	get_time(void);
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
void			error_msg(char *err_msg);


#endif
