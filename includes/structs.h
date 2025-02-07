#ifndef STRUCTS_H
# define STRUCTS_H
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"

struct s_philo;

typedef struct	s_data
{
	int				n_philos;
	unsigned int	time_to_die;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				n_meals;
	size_t			start_time;
	struct s_philo	*philos;
	pthread_t		*philo_threads;
	pthread_t		*monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*is_running_mutex;
} t_data;

typedef struct	s_philo
{
	unsigned int	id;
	int				n_meals;
	t_status		status;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	long			last_meal;
} t_philo;

void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	*routine(void *philo);
void	*monitor(void *data);

#endif