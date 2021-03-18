/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 11:27:42 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 15:13:32 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void			philo_sleep(uint64_t time)
{
	uint64_t	end;

	end = gettime_us() + time;
	while (gettime_us() < end)
		usleep(100);
}

unsigned char	eat(t_philo *philo)
{
	if (update_last_meal(philo))
		return (forks(philo, UNLOCK) || ERROR);
	philo_sleep(philo->env->time_to_eat);
	return (update_n_meal(philo));
}

unsigned char	forks(t_philo *philo, int type)
{
	t_env	*env;

	env = philo->env;
	if (type == LOCK)
	{
		if (pthread_mutex_lock(&philo->left_fork_mutex)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN))
			return (ERROR);
		if (pthread_mutex_lock(&env->philo[philo->n
					% env->n_threads].left_fork_mutex)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN))
			return (pthread_mutex_unlock(&philo->left_fork_mutex) || ERROR);
	}
	else if (pthread_mutex_unlock(&philo->left_fork_mutex)
			| pthread_mutex_unlock(
				&env->philo[philo->n % env->n_threads].left_fork_mutex))
		return (ERROR);
	return (SUCCESS);
}

void			*start_routine(void *tmp)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)tmp;
	env = philo->env;
	if (pthread_create(&philo->monitor_thread, NULL, monitor_philo, philo))
		return (thread_error(env));
	while (!death(philo->env))
	{
		if (forks(philo, LOCK)
			|| eat(philo)
			|| forks(philo, UNLOCK))
			return (thread_error(env));
		if (philo_log(philo, LOG_SLEEPING, LOG_SLEEPING_LEN))
			return (thread_error(env));
		philo_sleep(env->time_to_sleep);
		if (philo_log(philo, LOG_THINKING, LOG_THINKING_LEN))
			return (thread_error(env));
		usleep(100);
	}
	return (NULL);
}
