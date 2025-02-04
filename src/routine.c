#include "philosophers.h"


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(1, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	dream(t_philo *philo)
{
    philo->status = sleeping;
    message(philo->id, "is sleeping.");
    usleep(philo->data->sleep_time * 1000);
}

void	eat(t_philo *philo)
{
    if (philo->n_meals == 0) {
        message(philo->id, "has taken all its meals.\n");
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
        philo->status = eating;
        message(philo->id, "is eating.");
        philo->status = eating;
        usleep(philo->data->eat_time * 1000);
        if (philo->n_meals > 0)
           philo->n_meals--;
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        philo->last_meal = get_current_time();
    }
}

void	think(t_philo *philo)
{
    philo->status = thinking;
    message(philo->id, "is thinking.");
}

void    *routine(void *philo)
{
    t_philo *p;

    p = (t_philo *)philo;

    while (p->data->dead_philo_id == -1)
    {
        if (p->data->philos[p->id].n_meals != 0) {
            eat(p);
            dream(p);
            think(p);
        }
    }
    return (philo);
}

void    *monitor(void *data)
{
    t_data  *d;
    int     i;

    d = (t_data *)data;
    while (d->dead_philo_id == -1)
    {
        i = -1;
        while (++i < d->n_philos)
        {
            if (d->philos[i].n_meals > 0
                && get_current_time() - d->philos[i].last_meal > d->time_to_die)
            {
                d->dead_philo_id = i;
                message(d->philos[i].id, "died.");
                break ;
            }
        }
    }
    return (data);
}

void    start_dinner(t_data *data)
{
    int    i;
    pthread_create(data->monitor_thread, NULL, monitor, data);
    i = -1;
    while (++i < data->n_philos)
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philos[i].thread, NULL);
}
