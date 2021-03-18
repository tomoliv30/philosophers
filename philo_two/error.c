/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 11:35:05 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 20:40:18 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

unsigned char	impossible_sim(void)
{
	write(STDERR_FILENO, ERR_IMPOSSIBLE, ERR_IMPOSSIBLE_LEN);
	return (ERROR);
}

unsigned char	internal_err(void)
{
	write(STDERR_FILENO, ERR_INTERNAL, ERR_INTERNAL_LEN);
	return (ERROR);
}

void			*thread_error(t_env *env)
{
	sem_wait(env->death_sem);
	env->death = INTERNAL;
	sem_post(env->death_sem);
	sem_post(env->end_sem);
	return (NULL);
}

int				init_error(t_env *env, int type)
{
	if (env->death_sem)
		sem_wait(env->death_sem);
	env->death = type;
	if (env->death_sem)
		sem_post(env->death_sem);
	return (ERROR);
}
