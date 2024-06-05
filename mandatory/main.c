/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/04 00:53:54 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *worker(void *args)
{
    t_philo *philo = (t_philo *)args;

    while (1)
    {
        printf("Philosopher %d is thinking\n", philo->id);
        
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            printf("Philosopher %d has taken the left fork\n", philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("Philosopher %d has taken the right fork\n", philo->id);
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            printf("Philosopher %d has taken the right fork\n", philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("Philosopher %d has taken the left fork\n", philo->id);
        }

        printf("Philosopher %d is eating\n", philo->id);
        usleep(philo->time_to_eat * 1000);
        
        pthread_mutex_unlock(philo->left_fork);
        printf("Philosopher %d has put down the left fork\n", philo->id);
        pthread_mutex_unlock(philo->right_fork);
        printf("Philosopher %d has put down the right fork\n", philo->id);

        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(philo->time_to_sleep * 1000);
    }
    return NULL;
}

void init_data(t_data *data, int ac, char **av)
{
    int i;
    int num_philos;
	
	i = 0;
	num_philos = atoi(av[1]);

    data->philo = malloc(sizeof(t_philo) * num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);

    while (i < num_philos)
    {
        data->philo[i].id = i + 1;
        data->philo[i].num_of_philos = num_philos;
        data->philo[i].time_to_die = atoi(av[2]);
        data->philo[i].time_to_eat = atoi(av[3]);
        data->philo[i].time_to_sleep = atoi(av[4]);
        data->philo[i].num_times_to_eat = (ac == 6) ? atoi(av[5]) : -1;
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % num_philos];
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

int th_starting(t_data *data)
{
    int i = 0;

    while (i < data->philo->num_of_philos)
    {
        if (pthread_create(&data->philo[i].thread, NULL, worker, &data->philo[i]))
            return (printf("Failed to create philosopher number %d\n", i));
        i++;
    }

    i = 0;
    while (i < data->philo->num_of_philos)
    {
        if (pthread_join(data->philo[i].thread, NULL))
            return (printf("Failed to join philosopher number %d\n", i));
        i++;
    }
    return 0;
}

int main(int ac, char **av)
{
    t_data data;

    if (ac == 5 || ac == 6)
    {
        if (!ft_parce_args(ac, av))
            return ( printf("Error in the arguments. Retry again.\n"));
        init_data(&data, ac, av);
        th_starting(&data);
    }
    else
        return (printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]));
    return 0;
}
