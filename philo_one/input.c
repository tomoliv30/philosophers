/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 10:22:15 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/06 16:24:37 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned char	valid_number(char *arg)
{
	char	sign;
	int		parse;

	sign = arg[0];
	if (sign == '-')
		return (ERROR);
	else if (sign == '+')
		sign = 1;
	else
		sign = 0;
	parse = sign;
	while (arg[parse])
	{
		if (arg[parse] < '0' && arg[parse] > '9')
			return (ERROR);
		if (parse == 20 + sign)
			return (ERROR);
		parse++;
	}
	return (SUCCESS);
}

unsigned char	valid_args(int ac, char **av)
{
	int	arg;

	arg = 1;
	if (ac != 5 && ac != 6)
		return (ERROR);
	while (arg < ac)
	{
		if (valid_number(av[arg]))
			return (ERROR);
		arg++;
	}
	return (SUCCESS);
}
