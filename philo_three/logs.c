/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logs.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 16:05:30 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:22:22 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

size_t	fill_log_buf(t_philo *philo, uint64_t t_stamp, char const *log,
		size_t log_len)
{
	size_t	buf_len;
	size_t	write;
	int		i;

	write = sputnbr(t_stamp, philo->env->log_buf);
	philo->env->log_buf[write] = ' ';
	write++;
	write += sputnbr(philo->n, philo->env->log_buf + write);
	buf_len = write + log_len;
	i = 0;
	while (write < buf_len)
	{
		philo->env->log_buf[write] = log[i];
		write++;
		i++;
	}
	philo->env->log_buf[write] = '\0';
	return (buf_len);
}

int		philo_log(t_philo *philo, char const *log, size_t log_len)
{
	size_t	log_buf_len;

	sem_wait(philo->env->log_sem);
	if (death(philo->env))
		return (sem_post(philo->env->log_sem));
	log_buf_len = fill_log_buf(philo, gettime_ms() -
			philo->env->start_time,
			log, log_len);
	if (write(1, philo->env->log_buf, log_buf_len) == -1)
		return (sem_post(philo->env->log_sem));
	return (sem_post(philo->env->log_sem));
}
