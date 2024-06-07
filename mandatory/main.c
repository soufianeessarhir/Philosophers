/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/07 04:40:10 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eating(t_philo **philo, size_t start_time)
{
    (*philo)->last_time_eat = current_time();
    printf(MAGENTA"%zu %d is sleeping\n"RESET, current_time() - start_time, (*philo)->id);
}

void *a_worker(void *args)
{
    size_t start_time;
    
    start_time = current_time();
    t_data *data = (t_data *)args;
    int i;

    while (!data->dead_flag)
    {
        i = 0;
        while (i < data->num_of_philos)
        {
            if (current_time() - start_time > data->time_to_die)
            {
                pthread_mutex_lock(&data->dead_flag_mutex);
                data->dead_flag = 1;
                pthread_mutex_unlock(&data->dead_flag_mutex);
                printf(BOLD  RED"%zu %d has died\n"RESET, current_time() - start_time, data->philo[i].id);
                return NULL;
            }
            i++;
        }
    }
    return NULL;
}

void handle_forks_and_eat(t_philo *philo, size_t start_time)
{
    pthread_mutex_lock(philo->left_fork);
    printf(CYAN"%zu %d has taken a fork\n"RESET, current_time() - start_time, philo->id);
    pthread_mutex_lock(philo->right_fork);
    printf(CYAN"%zu %d has taken a fork\n"RESET, current_time() - start_time, philo->id);
    printf(YELLOW"%zu %d is eating\n"RESET, current_time() - start_time, philo->id);
    ft_usleep(philo->time_to_eat,philo);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    eating(&philo, start_time);
    ft_usleep(philo->time_to_sleep,philo);
    printf(GREEN"%zu %d is thinking\n"RESET, current_time() - start_time, philo->id);
}

void *worker(void *args)
{
    t_philo *philo = (t_philo *)args;
    t_data *data = philo->data;
    size_t start_time = current_time();

    if (philo->id % 2 == 0)
        usleep(50);
    while (1)
    {
    	pthread_mutex_lock(&data->dead_flag_mutex);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->dead_flag_mutex);
			break;
		}
		pthread_mutex_unlock(&data->dead_flag_mutex);
        handle_forks_and_eat(philo, start_time);
    }
    return NULL;
}


int th_starting(t_data *data)
{
    int i;
    
    i = 0;

    while (i < data->num_of_philos)
    {
        if (pthread_create(&data->philo[i].thread, NULL, worker, &data->philo[i]))
            return (printf(RED"Failed to create philosopher number %d\n"RESET, i));
        i++;
    }
    if (pthread_create(&data->admin, NULL, a_worker, data))
        return (printf(RED"Failed to create admin philosopher\n"RESET));
    i = 0;
    while (i < data->num_of_philos)
    {
        if (pthread_join(data->philo[i].thread, NULL))
            return (printf(RED"Failed to join philosopher number %d\n"RESET, i));
        i++;
    }
    pthread_detach(data->admin);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;

    if (ac == 5 || ac == 6)
    {
        if (!ft_parce_args(ac, av))
            return (printf(RED"Error in the arguments. Retry again.\n"RESET));
        init_data(&data, ac, av);
        th_starting(&data);
    }
    else
    {
        return (printf(UNDERLINE BOLD RED"Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"RESET, av[0]));
    }

    return 0;
}
