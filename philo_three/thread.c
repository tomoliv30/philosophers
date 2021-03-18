/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 16:57:36 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:24:58 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

void	*count_meals(void *tmp)
{
	int		n;
	t_env	*env;

	env = tmp;
	n = 0;
	while (n < env->n_threads && !death(env))
	{
		if (sem_wait(env->n_meals_sem))
			return (thread_error(env));
		n++;
	}
	if (die(env))
		return (thread_error(env));
	return (NULL);
}

void	*monitor_philo(void *tmp)
{
	t_philo	*philo;
	t_env	*env;

	philo = tmp;
	env = philo->env;
	while (time_left(philo))
		usleep(5000);
	exit(philo_log(philo, LOG_DIED, LOG_DIED_LEN)
			| die(env) | sem_post(env->n_meals_sem));
}

int		death(t_env *env)
{
	int	ret;

	ret = sem_wait(env->death_sem);
	ret |= env->death;
	ret |= sem_post(env->death_sem);
	return (ret);
}

int		die(t_env *env)
{
	int	status;

	status = sem_wait(env->death_sem);
	if (!env->death)
		env->death = 1;
	status |= sem_post(env->death_sem) | sem_post(env->end_sem);
	return (status);
}
