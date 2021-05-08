/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:32:42 by jfreitas          #+#    #+#             */
/*   Updated: 2021/05/08 02:31:32 by jfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 *
 */

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);

}

/*
 * Funtion called by the pthread_create function.
 * void *actions = &philo[i] whenre i > 0 && i < philo->nb.
 *
 * --------
 * philo eating → can't think or sleep.
 * philo sleeping → can't eat or think.
 * philo thinking → can't eat or sleep.
 *
 * Right after a philo stops eating, s/he puts down her/is fork and go sleep.
 * When a philosopher stops to sleep, s/he starts to think!!!
 */

void	*philo_actions(void *actions)
{
	t_philo	*philo;

	philo = (t_philo*)actions;
	while (philo->time_to_die >= 0)
	{
		philo_eat(philo);
		//philo_sleep();
		//philo_think();
	}
	return (NULL);
}
