/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 12:59:49 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 20:42:48 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <fcntl.h>

int	close_env_sem(t_env *env)
{
	return ((env->death_sem && sem_close(env->death_sem))
			| (env->log_sem && sem_close(env->log_sem))
			| (env->forks_sem && sem_close(env->forks_sem))
			| (env->n_meals_sem && sem_close(env->n_meals_sem))
			| (env->last_meal_sem && sem_close(env->last_meal_sem))
			| (env->end_sem && sem_close(env->end_sem))
			| sem_unlink(SEM_DEATH)
			| sem_unlink(SEM_LOG)
			| sem_unlink(SEM_FORKS)
			| sem_unlink(SEM_NMEALS)
			| sem_unlink(SEM_LASTMEAL)
			| sem_unlink(SEM_END));
}

int	open_sem(sem_t **sem, char *type, int value)
{
	sem_unlink(type);
	*sem = sem_open(type, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

int	open_env_sem(t_env *env)
{
	return (open_sem(&env->forks_sem, SEM_FORKS, env->n_threads)
				|| open_sem(&env->log_sem, SEM_LOG, 1)
				|| open_sem(&env->end_sem, SEM_END, 0)
				|| open_sem(&env->last_meal_sem, SEM_LASTMEAL, 1)
				|| open_sem(&env->n_meals_sem, SEM_NMEALS, 0)
				|| open_sem(&env->death_sem, SEM_DEATH, 1));
}
