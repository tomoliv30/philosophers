/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 13:13:36 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:24:06 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/time.h>

uint64_t		gettime_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((uint64_t)((t.tv_sec * (uint64_t)1000)
				+ (t.tv_usec * 0.001)));
}

uint64_t		gettime_us(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

bool			time_left(t_philo *philo)
{
	bool	ret;

	sem_wait(philo->env->last_meal_sem);
	ret = gettime_ms() - philo->last_meal
			< philo->env->time_to_die;
	sem_post(philo->env->last_meal_sem);
	return (ret);
}
