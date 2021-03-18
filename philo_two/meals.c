/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meals.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 11:45:24 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 15:24:55 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				update_last_meal(t_philo *philo)
{
	if (sem_wait(philo->env->last_meal_sem))
		return (ERROR);
	philo->last_meal = gettime_ms();
	return (sem_post(philo->env->last_meal_sem)
		|| philo_log(philo, LOG_EAT, LOG_EAT_LEN));
}

int				update_n_meal(t_philo *philo)
{
	if (philo->n_meals <= 0)
		return (SUCCESS);
	philo->n_meals--;
	return (!philo->n_meals && sem_post(philo->env->n_meals_sem));
}
