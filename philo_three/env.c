/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 13:45:53 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 14:26:11 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int	init_philo(t_env *env)
{
	int	philo;

	philo = 0;
	env->philo = malloc(sizeof(t_philo) * env->n_threads);
	if (!env->philo)
		return (init_error(env, INTERNAL));
	memset(env->philo, 0, env->n_threads);
	while (philo < env->n_threads)
	{
		env->philo[philo].env = env;
		env->philo[philo].n = philo + 1;
		env->philo[philo].pid = -1;
		env->philo[philo].last_meal = env->start_time;
		env->philo[philo].n_meals = env->count_meals;
		philo++;
	}
	return (SUCCESS);
}

int	init_env(int ac, char **av, t_env *env)
{
	memset(env, 0, sizeof(*env));
	if (valid_args(ac, av))
		return (init_error(env, IMPOSSIBLE));
	env->start_time = gettime_ms();
	env->n_threads = ft_atoi(av[1]);
	if (env->n_threads <= 1)
		return (init_error(env, IMPOSSIBLE));
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]) * 1000;
	env->time_to_sleep = ft_atoi(av[4]) * 1000;
	env->count_meals = ac == 6;
	if (env->count_meals)
		env->count_meals = ft_atoi(av[5]);
	if (env->count_meals < 0)
		return (init_error(env, IMPOSSIBLE));
	env->death = 0;
	return (open_env_sem(env) || init_philo(env));
}

int	clear_philo(t_philo *philo)
{
	int		wstatus;
	t_env	*env;
	int		status;

	if (!philo)
		return (SUCCESS);
	wstatus = 0;
	env = philo->env;
	status = env->n_meals_sem && sem_post(env->n_meals_sem);
	if (philo->pid != -1)
		status |= waitpid(philo->pid, &wstatus, WNOHANG) == -1;
	status |= wstatus;
	if (philo->pid != -1 && !kill(philo->pid, 0))
		status |= kill(philo->pid, SIGKILL);
	return (status);
}

int	clear_env(t_env *env)
{
	int			status;
	int			philo;

	philo = 0;
	status = SUCCESS;
	while (philo < env->n_threads)
	{
		status |= (env->philo && env->philo + philo
				&& clear_philo(env->philo + philo));
		philo++;
	}
	status |= (env->count_meals && env->count_meals_thread
			&& pthread_join(env->count_meals_thread, NULL));
	status |= close_env_sem(env) | (env->death == INTERNAL);
	if (env->philo)
		free(env->philo);
	if (env->death == IMPOSSIBLE)
		return (impossible_sim());
	if (status)
		return (internal_err());
	return (SUCCESS);
}
