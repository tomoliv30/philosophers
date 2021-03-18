/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 13:45:53 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 11:22:47 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <string.h>
#include <stdlib.h>

unsigned char	init_philo(t_env *env)
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
		env->philo[philo].last_meal = env->start_time;
		env->philo[philo].n_meals = env->count_meals;
		if (pthread_mutex_init(&env->philo[philo].left_fork_mutex, NULL)
				|| pthread_mutex_init(&env->philo[philo].last_meal_mutex, NULL))
			return (init_error(env, INTERNAL));
		philo++;
	}
	return (SUCCESS);
}

int				init_env_mutex(t_env *env)
{
	return (pthread_mutex_init(&env->death_mutex, NULL)
			|| pthread_mutex_init(&env->log_mutex, NULL)
			|| pthread_mutex_init(&env->n_meal_mutex, NULL));
}

int				init_env(int ac, char **av, t_env *env)
{
	memset(env, 0, sizeof(*env));
	if (valid_args(ac, av))
		return (init_error(env, IMPOSSIBLE));
	env->start_time = gettime_ms();
	env->n_threads = ft_atoi(av[1]);
	if (env->n_threads <= 1)
		return (init_error(env, IMPOSSIBLE));
	env->philo_meals_left = env->n_threads;
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]) * 1000;
	env->time_to_sleep = ft_atoi(av[4]) * 1000;
	env->count_meals = ac == 6;
	if (env->count_meals)
		env->count_meals = ft_atoi(av[5]);
	if (env->count_meals < 0)
		return (init_error(env, IMPOSSIBLE));
	env->death = 0;
	return (init_env_mutex(env) || init_philo(env));
}

int				clear_philo_mutex(t_env *env)
{
	int	philo;

	philo = 0;
	while (philo < env->n_threads)
	{
		if (env->philo && env->philo + philo)
		{
			pthread_mutex_destroy(&env->philo[philo].left_fork_mutex);
			pthread_mutex_destroy(&env->philo[philo].last_meal_mutex);
		}
		philo++;
	}
	return (SUCCESS);
}

int				clear_env(t_env *env)
{
	int	status;

	status = (env->death == INTERNAL)
			| wait_threads(env)
			| clear_philo_mutex(env);
	pthread_mutex_destroy(&env->log_mutex);
	pthread_mutex_destroy(&env->n_meal_mutex);
	pthread_mutex_destroy(&env->death_mutex);
	if (env->philo)
		free(env->philo);
	if (env->death == IMPOSSIBLE)
		return (impossible_sim());
	if (status)
		return (internal_err());
	return (SUCCESS);
}
