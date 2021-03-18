/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 01:48:47 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:23:35 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

int	init_processes(t_env *env)
{
	t_philo *philo;
	int		n;

	philo = 0;
	n = 0;
	while (n < env->n_threads)
	{
		philo = env->philo + n;
		philo->pid = fork();
		if (philo->pid == -1)
			return (init_error(env, INTERNAL));
		if (philo->pid == 0)
		{
			if (pthread_create(&philo->monitor_thread, NULL, monitor_philo,
						philo)
				|| pthread_detach(philo->monitor_thread)
				|| start_routine(philo))
				exit(process_error(env));
			exit(SUCCESS);
		}
		n++;
	}
	return (SUCCESS);
}
