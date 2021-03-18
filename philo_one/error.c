/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 11:35:05 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/06 16:24:05 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
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
	pthread_mutex_lock(&env->death_mutex);
	env->death = INTERNAL;
	pthread_mutex_unlock(&env->death_mutex);
	return (NULL);
}

int				init_error(t_env *env, int type)
{
	env->death = type;
	return (ERROR);
}
