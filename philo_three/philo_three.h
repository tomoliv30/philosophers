/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 16:44:41 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/09 11:23:04 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# define LOG_FORK " has taken a fork\n"
# define LOG_EAT " is eating\n"
# define LOG_SLEEPING " is sleeping\n"
# define LOG_THINKING " is thinking\n"
# define LOG_DIED " died\n"
# define ERR_ARGS "error with arguments\n"
# define SEM_DEATH "/death"
# define SEM_LOG "/log"
# define SEM_FORKS "/forks"
# define SEM_LASTMEAL "/lastmeal"
# define SEM_NMEALS "/nmeals"
# define SEM_END "/end"
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
	int				n;
	pid_t			pid;
	uint64_t		last_meal;
	int				n_meals;
	struct s_env	*env;
	pthread_t		thread;
	pthread_t		monitor_thread;
}				t_philo;

typedef struct	s_env
{
	int				n_threads;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	int				count_meals;
	unsigned char	death;
	t_philo			*philo;
	pthread_t		count_meals_thread;
	sem_t			*death_sem;
	sem_t			*log_sem;
	sem_t			*forks_sem;
	sem_t			*n_meals_sem;
	sem_t			*last_meal_sem;
	sem_t			*end_sem;
	char			log_buf[39];
	uint64_t		start_time;
}				t_env;

int				clear_env(t_env *env);
int				init_env(int ac, char **av, t_env *env);

int				impossible_sim();
int				internal_err();
int				process_error(t_env *env);
void			*thread_error(t_env *env);
int				init_error(t_env *env, int type);

int				valid_args(int ac, char **av);

int				philo_log(t_philo *philo, char const *log, size_t log_len);

int				start_routine(void *tmp);

int				init_processes(t_env *env);

int				open_env_sem(t_env *env);
int				close_env_sem(t_env *env);

uint64_t		gettime_us();
uint64_t		gettime_ms();
bool			time_left(t_philo *philo);

int				die(t_env *env);
int				death(t_env *env);
void			*monitor_philo(void *tmp);
void			*count_meals(void *tmp);

int				ft_atoi(const char *str);
size_t			sputnbr(uint64_t n, char *buf);

#endif
