/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 16:22:17 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 13:29:28 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int ac, char **av)
{
	struct s_env	env;

	if (init_env(ac, av, &env)
		|| init_processes(&env)
		|| (env.count_meals
			&& pthread_create(&env.count_meals_thread,
				NULL, count_meals, &env)))
		return (clear_env(&env));
	sem_wait(env.end_sem);
	return (clear_env(&env));
}
