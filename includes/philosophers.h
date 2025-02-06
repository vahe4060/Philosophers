/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:30 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 17:01:06 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define USAGE "Usage:\n\
\t./philosophers [NUM_PHILOS] [TIME_TO_DIE] [TIME_TO_EAT]\
[TIME_TO_SLEEP] [[NUM_MEALS]]\n\
NUM_PHILOS\t- number of philosophers\n\
TIME_TO_DIE\t- maximum time each philosopher can spend hungry/thinking (ms)\n\
TIME_TO_EAT\t- time each philosopher spends eating (ms)\n\
TIME_TO_SLEEP\t- time each philosopher spends sleeping (ms)\n\
[NUM_MEALS]\t- optional, number of meals for each philosopher.\n"
#define MALLOC_ERROR "Memory Error\n"

typedef enum s_status {
	eating = 0,
	sleeping,
	thinking,
	dead,
	finished
} t_status;

static const char status_str[5][10] = {
	"eating   ",
	"sleeping ",
	"thinking ",
	"dead     ",
	"finished "
};

struct s_philo;

typedef struct	s_data
{
	int				n_philos;
	unsigned int	time_to_die;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				n_meals;
	int				dead_philo_id;
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
	size_t			last_meal;
} t_philo;

size_t	ft_strlen(const char *c);
void	log_philo_status(t_philo *philo);
void	log_time(long int start_time);
int		init_args(int argc, char **argv, t_data *data);
int		init_philos(t_data *data);
size_t	get_current_time(void);

void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	*routine(void *philo);
void	start_dinner(t_data *data);

#endif
