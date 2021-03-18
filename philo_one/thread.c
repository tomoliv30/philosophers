/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 16:57:36 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 11:04:09 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

unsigned char	init_threads(t_env *env)
{
	int	n;

	n = 0;
	while (n < env->n_threads)
	{
		if (pthread_create(&env->philo[n].thread, NULL,
				start_routine, env->philo + n))
			return (init_error(env, INTERNAL));
		usleep(100);
		n++;
	}
	return (SUCCESS);
}

int				wait_threads(t_env *env)
{
	int	philo;
	int	status;

	philo = 0;
	status = SUCCESS;
	while (philo < env->n_threads)
	{
		if (env->philo && env->philo + philo && env->philo[philo].thread)
			status |= pthread_join(env->philo[philo].thread, NULL);
		philo++;
	}
	return (status);
}
