/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:34:16 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 17:00:13 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

unsigned int	to_uint(char *str, int *status)
{
	long	number;

	if (*str == '+')
		str++;
	if (*str == '\0')
		*status = EXIT_FAILURE;
	while (*str == '0')
		++str;
	number = 0;
	while (*str != '\0' && *status == EXIT_SUCCESS)
	{
		if (*str <= '9' && *str >= '0')
			number = number * 10 + (*str++ - '0');
		else
			*status = EXIT_FAILURE;
		if (number > UINT_MAX)
			*status = EXIT_FAILURE;
	}
	return (number);
}

size_t	ft_strlen(const char *c)
{
	size_t	size;

	size = 0;
	while (c[size] != '\0')
		++size;
	return (size);
}

void    ft_putnbr(unsigned long int n)
{
    char    c;

    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void	log_philo_status(t_philo *philo)
{
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&print_mutex);
	write(1, "Philo ", 6);
	ft_putnbr(philo->id);
	write(1, ": ", 2);
	write(1, status_str[philo->status],	
		  ft_strlen(status_str[philo->status]));
	write(1, "\n", 1);
	pthread_mutex_unlock(&print_mutex);
}

void	log_time(long int start_time)
{
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&print_mutex);
	write(1, "Time: ", 6);
	ft_putnbr(get_current_time() - start_time);
	write(1, "ms\n", 3);
	pthread_mutex_unlock(&print_mutex);
}

int	init_args(int argc, char **argv, t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	if (argc != 5 && argc != 6)
		status = EXIT_FAILURE;
	if (!status)
		data->n_philos = to_uint(argv[1], &status);
	if (!status)
		data->time_to_die = to_uint(argv[2], &status);
	if (!status)
		data->eat_time = to_uint(argv[3], &status);
	if (!status)
		data->sleep_time = to_uint(argv[4], &status);
	data->n_meals = -1;
	if (!status && argc == 6)
		data->n_meals = to_uint(argv[5], &status);
	data->dead_philo_id = -1;
	return (status);
}

int init_philos(t_data *data)
{
	int	i;

	data->philo_threads = (pthread_t *)malloc(sizeof(pthread_t)
											  * data->n_philos);
	data->monitor_thread = (pthread_t *)malloc(sizeof(pthread_t));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 
			data->n_philos);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!data->monitor_thread || !data->philo_threads
		|| !data->forks || !data->philos)
		return (EXIT_FAILURE);
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->n_philos - 1];
	i = 0;
	while (++i < data->n_philos)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].status = thinking;
		data->philos[i].n_meals = data->n_meals;
		data->philos[i].last_meal = get_current_time();
		++i;
	}
	return (EXIT_SUCCESS);
}
