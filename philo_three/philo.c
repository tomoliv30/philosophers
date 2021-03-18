/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 14:28:50 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:25:20 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

void	philo_sleep(uint64_t time)
{
	uint64_t	end;

	end = gettime_us() + time;
	while (gettime_us() < end)
		usleep(100);
}

int		forks(t_philo *philo, int type)
{
	t_env	*env;

	env = philo->env;
	if (type == LOCK)
	{
		if (sem_wait(env->forks_sem)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN)
			|| sem_wait(env->forks_sem)
			|| philo_log(philo, LOG_FORK, LOG_FORK_LEN))
			return (ERROR);
	}
	else
		return (sem_post(env->forks_sem) || sem_post(env->forks_sem));
	return (SUCCESS);
}

int		eat(t_philo *philo)
{
	if (sem_wait(philo->env->last_meal_sem))
		return (forks(philo, UNLOCK) || ERROR);
	philo->last_meal = gettime_ms(philo->env);
	if (sem_post(philo->env->last_meal_sem)
		|| philo_log(philo, LOG_EAT, LOG_EAT_LEN))
		return (forks(philo, UNLOCK) || ERROR);
	philo_sleep(philo->env->time_to_eat);
	return (SUCCESS);
}

int		update_n_meal(t_philo *philo)
{
	if (philo->n_meals <= 0)
		return (SUCCESS);
	philo->n_meals--;
	return (!philo->n_meals && sem_post(philo->env->n_meals_sem));
}

int		start_routine(void *tmp)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)tmp;
	env = philo->env;
	if (pthread_create(&philo->monitor_thread, NULL, monitor_philo, philo)
		|| pthread_detach(philo->monitor_thread))
		return (ERROR);
	while (1)
	{
		if (forks(philo, LOCK)
			|| eat(philo)
			|| forks(philo, UNLOCK))
			return (ERROR);
		if (env->count_meals && update_n_meal(philo))
			return (ERROR);
		if (philo_log(philo, LOG_SLEEPING, LOG_SLEEPING_LEN))
			return (ERROR);
		philo_sleep(env->time_to_sleep);
		if (philo_log(philo, LOG_THINKING, LOG_THINKING_LEN))
			return (ERROR);
		usleep(1000);
	}
	return (SUCCESS);
}
