/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:55 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/11 21:15:50 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * destroyroyng all semaphore created and freeing any memory allocated.
 *
 * int sem_unlink(const char *name);
 */

void	terminate_semaphores(t_const_data *const_data)
{
	sem_close(const_data->check_death);
	sem_close(const_data->print_action);
	sem_close(const_data->fork);
	sem_unlink("check_death");
	sem_unlink("printf");
	sem_unlink("fork");
}

/*
 * pid_t waitpid(pid_t pid, int *stat_loc, int options);
 *
 * The waitpid() function suspends execution of its calling process (parent)
 * until stat_loc information is available for a terminated child process.
 * - pid -> specifies the set of child processes for which to wait.
 *   pid is equal to -1 so the calling process waits for any child to terminate.
 *   pid == return od fork which is the pid/id of the process.
 * - stat_loc -> is a pointer to the location where status information for The
 *   terminating process is to be stored and  can be evaluated with macros.
 *   Macro used:
 *   WIFEXITED(*stat_loc) != 0 -> process terminated normally.
 * - options -> specifies optional actions for the waitpid function.
 *   WUNTRACED causes the call to waitpid to return status information for a
 *   child  process that has either stopped or terminated.
 *   WNOHANG causes the call to waitpid to return status information
 *   immediately, without waiting for the specified child process to terminate.
 *
 *
 * int kill(pid_t pid, int sig);
 *
 * The kill() function sends the signal specified by sig to pid (a process).
 * - pid is id of the process to be killed.
 * - sig SIGKILL -> terminate/kill process program.
 */

void	terminate_process(t_philo *philo, t_const_data *const_data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < const_data->nb_philos)
	{
		waitpid(philo[i].process, &ret, WUNTRACED);
		if (WIFEXITED(ret))
		{
			i = 0;
			while (i < const_data->nb_philos)
			{
				kill(philo[i].process, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	error_msg(char *err_msg, int args_accepted)
{
	if (args_accepted)
	{
		printf(COLOR_YELLOW);
		printf("Optional: -dt (flag to check status' time difference)\n");
		printf(COLOR_GREEN);
		printf("number_of_philosophers\n");
		printf("time_to_die\n");
		printf("time_to_eat\n");
		printf("time_to_sleep\n");
		printf(COLOR_YELLOW);
		printf("Optional: number_of_times_each_philosopher_must_eat\n");
		printf(COLOR_RESET);
	}
	else
		printf("%s\n", err_msg);
}
