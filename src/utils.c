/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:34:16 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 17:00:13 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(1, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned int    to_uint(const char *str, int *status)
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

void	message(const char *str)
{
	write(1, str, ft_strlen(str));
}

void	log_philo_status(t_philo *philo)
{
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&print_mutex);
	message("Philo ");
	ft_putnbr(philo->id);
	message(": ");
	message(color[philo->status]);
	message(status_str[philo->status]);
	message(color[5]);
	message("\n");
	pthread_mutex_unlock(&print_mutex);
}

void	log_time(long int start_time)
{
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&print_mutex);
	message("Time: ");
	ft_putnbr(get_current_time() - start_time);
	message("ms\n");
	pthread_mutex_unlock(&print_mutex);
}