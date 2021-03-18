/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 11:27:42 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 20:42:20 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

void	philo_sleep(uint64_t time)
{
	uint64_t	end;

	end = gettime_us() + time;
	while (gettime_us() < end)
		usleep(100);
}

int		eat(t_philo *philo)
{
	if (update_last_meal(philo))
		return (forks(philo, UNLOCK) || ERROR);
	philo_sleep(philo->env->time_to_eat);
	return (SUCCESS);
}

int		forks(t_philo *philo, int type)
{
	t_env	*env;

	env = philo->env;
	if (type == LOCK)
	{
		if (sem_wait(env->forks_sem)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN))
			return (ERROR);
		if (sem_wait(env->forks_sem)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN))
			return (sem_post(env->forks_sem) || ERROR);
	}
	else if (sem_post(env->forks_sem)
			| sem_post(env->forks_sem))
		return (ERROR);
	return (SUCCESS);
}

void	*start_routine(void *tmp)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)tmp;
	env = philo->env;
	if (pthread_create(&philo->monitor_thread, NULL, monitor_philo, philo))
		return (thread_error(env));
	while (!death(philo->env, NULL))
	{
		if (forks(philo, LOCK)
			|| eat(philo)
			|| forks(philo, UNLOCK))
			return (thread_error(env));
		if (philo->n_meals > 0 && update_n_meal(philo))
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
