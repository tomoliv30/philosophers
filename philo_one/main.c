/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 16:22:17 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/06 16:27:49 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int ac, char **av)
{
	struct s_env	env;

	if (init_env(ac, av, &env)
			|| init_threads(&env)
			|| monitor_all(&env))
		return (clear_env(&env));
	return (clear_env(&env));
}
