/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_semaphore.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:25:38 by jfreitas          #+#    #+#             */
/*   Updated: 2021/08/11 22:51:56 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * Creating the same amount of the "number_of_philosopher" input, of precesses
 * on the program and calling the process_parent whith the index of the
 * structure as it's only paramenter.
 *
 * A process is the instance of a computer program that is being executed
 * by one or many threads.
 *
 * Fork - creates a new copy called "child" out of the original process that
 * is called "parent", they run concurrently.
 *
 *
 * On success:
 * the PID of the child process is returned in the parent, and 0 is returned
 * in the child.
 *
 * On failure:
 * -1 is returned in the parent, no child process is created.
 */

int	init_process_philos(t_philo *philo, t_const_data *const_data)
{
	int	i;

	i = 0;
	const_data->start_time = get_current_time();
	printf("%ld\n", const_data->start_time);
	while (i < const_data->nb_philos && const_data->time_to_die >= 0)
	{
		philo[i].const_data = const_data;
		philo[i].process = fork();
		if (philo[i].process < 0)
			return (FAIL);
		if (philo[i].process == 0)
			child_process(&philo[i]);
		if (const_data->one_philo_died == TRUE || philo[i].satisfied == TRUE)
			exit(FAIL);
		usleep(ONE_MS);
		i++;
	}
	return (SUCCESS);
}

/*
 * Initializating a semaphore to each fork (which is the "number_of_philosopher"
 * given as input by the user).
 *
 * sem_t *sem_open(const char *name, int oflag, ...);
 *
 * The philo->printf semaphore is to lock a thread to write on the screen while
 * another thread is already doing it, so we don't have scrambled output.
 *
 * The const_data->check_death is to lock a philo thread to do anything (mainly
 * eating) at the same time s/he has died.
 */

void	init_semaphores(t_const_data *const_data)
{
	sem_unlink("print_action");
	sem_unlink("check_death");
	sem_unlink("fork");
	const_data->print_action = sem_open("print_action", O_CREAT, S_IRWXU, 1);
	const_data->check_death = sem_open("check_death", O_CREAT, S_IRWXU, 1);
	const_data->fork = sem_open("fork", O_CREAT, S_IRWXU,
			const_data->nb_philos);
}
