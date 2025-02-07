#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>
#include <unistd.h>
#include "philosophers.h"


unsigned int    to_uint(const char *str, int *status);
size_t	ft_strlen(const char *c);
void	ft_putnbr(unsigned long int n);
void	message(const char *str);

void	log_philo_status(t_philo *philo);
void	log_time(long int start_time);

int		init_args(int argc, char **argv, t_data *data);
int		init_philos(t_data *data);

size_t	get_current_time(void);

#endif