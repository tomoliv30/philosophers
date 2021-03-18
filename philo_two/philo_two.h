/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: totartar <totartar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 12:29:55 by totartar      #+#    #+#                 */
/*   Updated: 2021/01/08 16:12:28 by totartar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdint.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define LOG_FORK " has taken a fork\n"
# define LOG_EAT " is eating\n"
# define LOG_SLEEPING " is sleeping\n"
# define LOG_THINKING " is thinking\n"
# define LOG_DIED " died\n"
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
	int				philo_meals_left;
	int				count_meals;
	unsigned char	death;
	pthread_t		count_meals_thread;
	t_philo			*philo;
	sem_t			*death_sem;
	sem_t			*log_sem;
	sem_t			*forks_sem;
	sem_t			*n_meals_sem;
	sem_t			*last_meal_sem;
	sem_t			*end_sem;
	char			log_buf[39];
	uint64_t		start_time;
}				t_env;

int				init_env(int ac, char **av, t_env *env);
int				clear_env(t_env *env);

unsigned char	impossible_sim(void);
unsigned char	internal_err(void);
void			*thread_error(t_env *env);
int				init_error(t_env *env, int type);

int				valid_args(int ac, char **av);
int				philo_log(t_philo *philo, char const *log, size_t log_len);

int				update_n_meal(t_philo *philo);
int				update_last_meal(t_philo *philo);

bool			death(t_env *env, int *status);
int				die(t_env *env);
void			*monitor_philo(void *tmp);

int				open_env_sem(t_env *env);
int				close_env_sem(t_env *env);

void			*start_routine(void *tmp);
int				forks(t_philo *philo, int type);

int				wait_threads(t_env *env);
int				init_threads(t_env *env);
void			*count_meals(void *tmp);

uint64_t		gettime_ms(void);
uint64_t		gettime_us(void);
bool			time_left(t_philo *philo);

size_t			sputnbr(uint64_t n, char *buf);
int				ft_atoi(const char *str);

#endif
