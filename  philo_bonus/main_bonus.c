/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:52 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/09 04:26:09 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

// void destroy_sem(t_philo *data)
// {
//     int i;

//     i = -1;
//     while (++i < data->num_of_philos)
//     {
//         sem_close(data->philo[i].left_fork);
// 		sem_close(data->philo[i].right_fork);
//     }
// }

// int meales_eaten(t_data *data)
// {
//     int i;
//     if (data->philo->num_times_to_eat == -1)
//         return 0;
//     i = -1;
//     while (++i < data[0].num_of_philos)
//         if (data->philo[i].num_times_eaten < data->philo[i].num_times_to_eat)
//             return 0;
//     return 1;
// }
void *a_worker(void *args)
{
    int i;
    t_philo *philo;
    
    philo = (t_philo *)args;
	while (1)
	{
		i = -1;
		while (++i < philo->num_of_philos)
		{
			sem_wait(philo->dead);
			if (current_time() - philo->last_time_eat > philo->time_to_die /*|| meales_eaten(philo)*/)
			{
				ft_message(philo, "died", BOLD_RED);
				// sem_wait(philo->dead);
				// *philo->dead = 1;
				sem_post(philo->dead);
				// sem_post(philo->philo[i].time_sem);
				exit(1);
			}
			sem_post(philo->dead);
			usleep(100);
		}
	}
    return NULL;
}
void *worker(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *)args;
    if (philo->id % 2 == 0) 
	ft_usleep(1, philo);
   	while (1)
    {
		sem_wait(philo->fork);
		ft_message(philo, "has taken a fork", CYAN);
		sem_wait(philo->fork);
		ft_message(philo, "has taken a fork", CYAN);
		ft_message(philo, "is eating", GREEN);
		philo->last_time_eat = current_time();
		philo->num_times_eaten++;
		ft_usleep(philo->time_to_eat, philo);
		sem_post(philo->fork);
		sem_post(philo->fork);
		ft_message(philo, "is sleeping", MAGENTA);
		ft_usleep(philo->time_to_sleep, philo);
		ft_message(philo, "is thinking", YELLOW);
    }
    return NULL;
}
int child_process(t_philo *philo)
{
	philo->id++;
	philo->num_times_eaten = 0;
	if (pthread_create(&philo->philo, NULL, a_worker, philo))
		return (printf(RED"Error in the thread\n"RESET), 1);
	worker(philo);
	exit(0);
	return 0;
}

int parent_process(t_philo *philo ,int *pid)
{
	int i;
	int status;

	i = -1;
	while (++i < philo->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->num_of_philos)
			{
               kill(pid[i], SIGKILL);
			}
			return 1;
		}
	}
	return 0;
}

int th_starting(t_philo *philo) 
{
    int i;
	int *pid;

	philo->start_time = current_time();
    pid = malloc(sizeof(int) * philo->num_of_philos);
	i = -1;
	while (++i < philo->num_of_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
		  philo->id = i;
		  break;
		}
		if (pid[i] < 0)
			return (printf(RED"Error in the fork\n"RESET));
	}
	if (pid[philo->id] == 0 && child_process(philo))
		return 1;
	else
	   parent_process(philo, pid);
	free(pid);
	return 0;
}
int main(int ac, char **av)
{
    t_philo philo;
    if (ac == 5 || ac == 6)
    {
        if (!ft_parce_args(ac, av))
            return (printf(RED"Error in the arguments. Retry again.\n"RESET));
        init_philo(&philo, ac, av);
        th_starting(&philo);
    }
    else
        return (printf(UNDERLINE BOLD RED"Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"RESET, av[0]));
    return 0;
}
