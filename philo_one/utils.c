/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 15:11:49 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/06 16:46:17 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include <limits.h>

static int	ft_is_blank(char c)
{
	return (c == '\t' || c == '\v' || c == '\f'
				|| c == '\r' || c == '\n' || c == ' ');
}

static int	ft_convert(const char *str, int sign)
{
	long int	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (result && LONG_MAX / result == 10)
			return (((int)result * 10 + (str[i] - '0')) * sign);
		if (result && LONG_MAX / result < 10 && sign == -1)
			return (0);
		if (result && LONG_MAX / result < 10 && sign == 1)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (((int)result) * sign);
}

int			ft_atoi(const char *str)
{
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	while (ft_is_blank(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_convert(str + i, sign));
}

size_t		write_reverse(uint64_t n, char *buf)
{
	size_t	len;

	len = 0;
	while (n)
	{
		buf[len] = '0' + n % 10;
		n *= 0.1;
		len++;
	}
	return (len);
}

size_t		sputnbr(uint64_t n, char *buf)
{
	size_t	start;
	char	swap;
	size_t	end;
	size_t	len;

	end = 0;
	if (!n)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return (1);
	}
	start = write_reverse(n, buf);
	buf[start] = '\0';
	len = start;
	start--;
	while (start > end)
	{
		swap = buf[end];
		buf[end] = buf[start];
		buf[start] = swap;
		start--;
		end++;
	}
	return (len);
}
