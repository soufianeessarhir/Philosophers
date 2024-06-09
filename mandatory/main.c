/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/09 02:28:34 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_message(t_philo *philo, char *text, char *color)
{
    pthread_mutex_lock(&philo->data->message);
    pthread_mutex_lock(&philo->data->dead_flag_mutex);
    if (!philo->data->dead_flag)
	{
        printf("%s""%zu %d %s\n" RESET, color, current_time() - philo->data->start_time, philo->id, text);
    	pthread_mutex_unlock(&philo->data->dead_flag_mutex);
	}
    pthread_mutex_unlock(&philo->data->dead_flag_mutex);
    pthread_mutex_unlock(&philo->data->message);
}
void *a_worker(void *args)
{
    int i;
    
    t_data *data = (t_data *)args;
    while (!data->dead_flag)
    {
        i = 0;
        while (i < data->num_of_philos)
        {
            pthread_mutex_lock(&data->philo[i].time_mutex);
            if (current_time() - data->philo[i].last_time_eat >= data->time_to_die)
            {
                pthread_mutex_lock(&data->dead_flag_mutex);
                data->dead_flag = 1;
                pthread_mutex_unlock(&data->dead_flag_mutex);
                pthread_mutex_lock(&data->message);
                printf(BOLD  RED"%zu %d has died\n"RESET, current_time() - data->start_time, data->philo[i].id);
                pthread_mutex_unlock(&data->message);
           		pthread_mutex_unlock(&data->philo[i].time_mutex);
                return NULL;
            }
           	pthread_mutex_unlock(&data->philo[i].time_mutex);
			i++;
        }
    }
    return NULL;
}

void handle_forks_and_eat(t_philo **philo)
{
    pthread_mutex_lock(&(*philo)->data->dead_flag_mutex);
    if ((*philo)->data->dead_flag)
    {
        pthread_mutex_unlock(&(*philo)->data->dead_flag_mutex);
        return;
    }
    pthread_mutex_unlock(&(*philo)->data->dead_flag_mutex);
    pthread_mutex_lock((*philo)->left_fork);
    ft_message((*philo),"has taken a fork",CYAN);
    pthread_mutex_lock((*philo)->right_fork);
    ft_message((*philo),"has taken a fork",CYAN);
    pthread_mutex_lock(&(*philo)->time_mutex);
    (*philo)->last_time_eat = current_time();
    ft_message((*philo), "is eating", YELLOW);
    pthread_mutex_unlock(&(*philo)->time_mutex);
    ft_usleep((*philo)->time_to_eat,(*philo));
    pthread_mutex_unlock((*philo)->left_fork);
    pthread_mutex_unlock((*philo)->right_fork);
    ft_message((*philo),"is sleeping",MAGENTA);
    ft_usleep((*philo)->time_to_sleep,(*philo));
    ft_message((*philo),"is thinking",GREEN);
}

void *worker(void *args)
{
    t_philo *philo = (t_philo *)args;
    if (philo->id % 2 == 0)
        usleep(50);
   	while (!philo->data->dead_flag)
    {
    	pthread_mutex_lock(&philo->data->dead_flag_mutex);
		if (philo->data->dead_flag)
		{
			
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(&philo->data->dead_flag_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->dead_flag_mutex);
        handle_forks_and_eat(&philo);
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
	pthread_join(data->admin, NULL);
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
