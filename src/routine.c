/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:09:27 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 16:56:09 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dream(t_philo *philo)
{
    if (philo->status == FINISHED)
        return ;
    philo->status = SLEEPING;
    usleep(philo->data->sleep_time * 1000);
}

void	eat(t_philo *philo)
{
    if (philo->status == FINISHED)
        return ;
    if (philo->n_meals == 0) {
        philo->status = FINISHED;
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
        philo->status = EATING;
        usleep(philo->data->eat_time * 1000);
        if (philo->n_meals > 0) // if num_meals is set
           philo->n_meals--;
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        philo->last_meal = get_current_time();
    }
}

void	think(t_philo *philo)
{
    if (philo->status != FINISHED)
        philo->status = THINKING;
}

void    *routine(void *philo)
{
    t_philo *p;

    p = (t_philo *)philo;
    while (p->status != FINISHED && p->terminate == 0)
    {
        eat(p);
        dream(p);
        think(p);
    }
    return (NULL);
}

void    *monitor(void *data)
{
    t_data  *d;
    int     i;
    int     dead_philo_id;
    int     status_changed;
    int     n_finished;

    n_finished = 0;
    status_changed = 1;
    dead_philo_id = -1;
    d = (t_data *)data;
    t_status prev_status[d->n_philos];
    i = -1;
    while (++i < d->n_philos)
        prev_status[i] = d->philos[i].status;
    while (dead_philo_id < 0 && n_finished < d->n_philos)
    {
        n_finished = 0;
        i = -1;
        while (++i < d->n_philos)
        {
            if (d->philos[i].status == FINISHED)
                n_finished++;
            else if (d->philos[i].status != EATING &&
                     get_current_time() - d->philos[i].last_meal > d->time_to_die)
            {
                dead_philo_id = i;
                d->philos[i].status = DEAD;
            }
            if (prev_status[i] != d->philos[i].status)
            {
                status_changed = 1;
                prev_status[i] = d->philos[i].status;
            }
        }
        if (status_changed)
        { // log status if there are any changes in status of any philo
            log_time(d->start_time);
            i = -1;
            while (++i < d->n_philos)
                log_philo_status(&d->philos[i]);
            status_changed = 0;
        }
    }
    if (dead_philo_id >= 0)
    {
        i = -1;
        while (++i < d->n_philos)
            d->philos[i].terminate = 1;
    }
    return (NULL);
}

void    start_dinner(t_data *data)
{
    int    i;

    data->start_time = get_current_time();
    pthread_create(data->monitor_thread, NULL, monitor, data);
    i = -1;
    while (++i < data->n_philos)
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philos[i].thread, NULL);
    pthread_join(*data->monitor_thread, NULL);
    destroy_data(data);
}

void    destroy_data(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->n_philos)
        pthread_mutex_destroy(data->philos[i].l_fork);
    free(data->philos);
    free(data->forks);
    free(data->philo_threads);
    free(data->monitor_thread);
}