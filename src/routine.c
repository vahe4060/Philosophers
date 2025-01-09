#include "philosophers.h"

void    ft_putnbr(unsigned int n)
{
    char    c;

    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void	dream(t_philo *philo)
{
    philo->status = sleeping;
    ft_putnbr(philo->id);
    message(" is sleeping.\n");
    usleep(philo->data->sleep_time * 1000);
}

void	eat(t_philo *philo)
{
    ft_putnbr(philo->id);
    if (philo->n_meals == 0)
        message(" has taken all its meals, skipping.\n");
    else
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
        philo->status = eating;
        message(" is eating.\n");
        philo->status = eating;
        usleep(philo->data->eat_time * 1000);
        if (philo->n_meals > 0)
           philo->n_meals--;
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
    }
}

void	think(t_philo *philo)
{
    philo->status = thinking;
    ft_putnbr(philo->id);
    message(" is thinking.\n");
}

void    *routine(void *philo)
{
    t_philo *p;

    p = (t_philo *)philo;

    while (p->data->dead_philo_id == -1)
    {
        eat(p);
        dream(p);
        think(p);
    }
    return (NULL);
}

void    start_dinner(t_data *data)
{
    int    i;

    i = -1;
    while (++i < data->n_philos)
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philos[i].thread, NULL);
}
