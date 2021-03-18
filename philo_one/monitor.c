/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 16:42:44 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 12:16:01 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

bool			death(t_env *env)
{
	bool	ret;

	if (pthread_mutex_lock(&env->death_mutex))
		return (true);
	ret = env->death;
	if (pthread_mutex_unlock(&env->death_mutex))
		return (true);
	return (ret);
}

int				die(t_env *env)
{
	if (pthread_mutex_lock(&env->death_mutex))
		return (ERROR);
	if (!env->death)
		env->death = 1;
	return (pthread_mutex_unlock(&env->death_mutex));
}

void			*monitor_philo(void *tmp)
{
	t_philo *philo;
	t_env	*env;

	philo = tmp;
	env = philo->env;
	while (time_left(philo) && (!env->count_meals || meals_left(philo->env)))
		usleep(5000);
	if (death(env))
		return (NULL);
	if (philo_log(philo, LOG_DIED, LOG_DIED_LEN) | die(env))
		return (thread_error(env));
	return (NULL);
}

int				monitor_all(t_env *env)
{
	int	philo;

	philo = 0;
	while (philo < env->n_threads)
	{
		pthread_join(env->philo[philo].monitor_thread, NULL);
		philo++;
	}
	return (SUCCESS);
}
