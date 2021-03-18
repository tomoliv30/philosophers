/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 15:34:00 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/07 10:34:22 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>

# define LOG_FORK " has taken a fork\n"
# define LOG_EAT " is eating\n"
# define LOG_SLEEPING " is sleeping\n"
# define LOG_THINKING " is thinking\n"
# define LOG_DIED " died\n"
# define ERR_IMPOSSIBLE "simulation not possible\n"
# define ERR_INTERNAL "internal error\n"

enum			e_num
{
	LOCK = 0,
	UNLOCK = 1,
	SUCCESS = 0,
	ERROR = 1,
	INTERNAL = 2,
	IMPOSSIBLE = 3,
	LOG_FORK_LEN = 18,
	LOG_EAT_LEN = 11,
	LOG_SLEEPING_LEN = 13,
	LOG_THINKING_LEN = 13,
	LOG_DIED_LEN = 6,
	ERR_IMPOSSIBLE_LEN = 24,
	ERR_INTERNAL_LEN = 15,
};

typedef struct	s_philo
{
	uint64_t		n;
	uint64_t		last_meal;
	int				n_meals;
	struct s_env	*env;
	pthread_t		thread;
	pthread_t		monitor_thread;
	pthread_mutex_t	left_fork_mutex;
	pthread_mutex_t last_meal_mutex;
}				t_philo;

typedef struct	s_env
{
	int				n_threads;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	int				count_meals;
	int				philo_meals_left;
	unsigned char	death;
	t_philo			*philo;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t log_mutex;
	pthread_mutex_t n_meal_mutex;
	char			log_buf[39];
	uint64_t		start_time;
}				t_env;

unsigned char	init_philo(t_env *env);
int				init_env_mutex(t_env *env);
int				init_env(int ac, char **av, t_env *env);
int				clear_philo_mutex(t_env *env);
int				clear_env(t_env *env);

unsigned char	impossible_sim(void);
unsigned char	internal_err(void);
void			*thread_error(t_env *env);
int				init_error(t_env *env, int type);

unsigned char	valid_args(int ac, char **av);

unsigned char	philo_log(t_philo *philo, char const *log, size_t log_len);

int				update_last_meal(t_philo *philo);
int				update_n_meal(t_philo *philo);
bool			meals_left(t_env *env);

bool			death(t_env *env);
int				die(t_env *env);
void			*monitor_philo(void *tmp);
int				monitor_all(t_env *env);

void			philo_sleep(uint64_t time);
unsigned char	eat(t_philo *philo);
unsigned char	forks(t_philo *philo, int type);
void			*start_routine(void *tmp);

unsigned char	init_threads(t_env *env);
int				wait_threads(t_env *env);

uint64_t		gettime_ms(void);
uint64_t		gettime_us(void);
bool			time_left(t_philo *philo);

int				ft_atoi(const char *str);
size_t			sputnbr(uint64_t n, char *buf);

#endif
