/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meals.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 16:41:14 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 11:48:41 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				update_last_meal(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->last_meal_mutex))
		return (ERROR);
	philo->last_meal = gettime_ms();
	return (pthread_mutex_unlock(&philo->last_meal_mutex)
			|| philo_log(philo, LOG_EAT, LOG_EAT_LEN));
}

int				update_n_meal(t_philo *philo)
{
	if (philo->n_meals > 0)
	{
		philo->n_meals--;
		if (!philo->n_meals)
		{
			if (pthread_mutex_lock(&philo->env->n_meal_mutex))
				return (forks(philo, UNLOCK) || ERROR);
			if (philo->env->philo_meals_left > 0)
				philo->env->philo_meals_left--;
			if (!philo->env->philo_meals_left)
			{
				if (pthread_mutex_unlock(&philo->env->n_meal_mutex))
					return (forks(philo, UNLOCK) || ERROR);
				die(philo->env);
			}
			else if (pthread_mutex_unlock(&philo->env->n_meal_mutex))
				return (forks(philo, UNLOCK) || ERROR);
		}
	}
	return (SUCCESS);
}

bool			meals_left(t_env *env)
{
	bool	ret;

	pthread_mutex_lock(&env->n_meal_mutex);
	ret = env->philo_meals_left;
	pthread_mutex_unlock(&env->n_meal_mutex);
	return (ret);
}
