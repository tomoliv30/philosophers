/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 16:57:36 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 20:43:47 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

void	*count_meals(void *tmp)
{
	int		n;
	t_env	*env;

	env = tmp;
	n = 0;
	while (n < env->n_threads && !death(env, NULL))
	{
		if (sem_wait(env->n_meals_sem))
			return (thread_error(env));
		n++;
	}
	if (die(env))
		return (thread_error(env));
	return (NULL);
}

int		init_threads(t_env *env)
{
	int	n;

	n = 0;
	while (n < env->n_threads)
	{
		if (pthread_create(&env->philo[n].thread, NULL,
				start_routine, env->philo + n))
			return (ERROR);
		usleep(100);
		n++;
	}
	return (SUCCESS);
}

int		wait_threads(t_env *env)
{
	int		philo;
	int		status;

	philo = 0;
	status = 0;
	while (philo < env->n_threads)
	{
		if (env->forks_sem)
			status |= sem_post(env->forks_sem);
		if (env->philo && env->philo + philo && env->philo[philo].thread)
			status |= pthread_join(env->philo[philo].thread, NULL);
		if (env->philo && env->philo + philo &&
				env->philo[philo].monitor_thread)
			status |= pthread_join(env->philo[philo].monitor_thread, NULL);
		philo++;
	}
	return (status);
}
