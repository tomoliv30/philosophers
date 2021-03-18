/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 12:04:48 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 20:41:39 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

bool	death(t_env *env, int *status)
{
	bool	ret;

	if (sem_wait(env->death_sem))
		return (true);
	if (status)
		*status = env->death;
	ret = env->death;
	if (sem_post(env->death_sem))
		return (true);
	return (ret);
}

int		die(t_env *env)
{
	if (sem_wait(env->death_sem))
		return (ERROR);
	if (!env->death)
		env->death = 1;
	return (sem_post(env->death_sem) | sem_post(env->end_sem));
}

void	*monitor_philo(void *tmp)
{
	t_philo *philo;
	t_env	*env;
	int		status;

	philo = tmp;
	env = philo->env;
	status = 0;
	while (time_left(philo) && !death(env, &status))
		usleep(5000);
	if (status)
		return (NULL);
	if (philo_log(philo, LOG_DIED, LOG_DIED_LEN) | die(env))
		return (thread_error(env));
	return (NULL);
}
