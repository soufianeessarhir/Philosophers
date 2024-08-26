/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:52 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/26 18:14:12 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

void *a_worker(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *)args;
	while (1)
	{
			sem_wait(philo->eat[philo->id]);
			sem_wait(philo->dead);
			if (current_time() - philo->last_time_eat > philo->time_to_die)
			{
				sem_wait(philo->message);
				printf("%s""%zu %d %s\n" RESET, BOLD_RED, current_time() - philo->start_time, philo->id, "died");
				sem_post(philo->dead);
				sem_post(philo->eat[philo->id]);
				exit(1);
			}
			sem_post(philo->dead);
			sem_post(philo->eat[philo->id]);
			usleep(100);
	}
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
		ft_usleep(philo->time_to_eat, philo);
		sem_wait(philo->eat[philo->id]);
		sem_wait(philo->dead);
		if (philo->num_times_to_eat != -1 && philo->num_times_eaten == philo->num_times_to_eat)
			exit(1); 
		philo->last_time_eat = current_time();
		philo->num_times_eaten++;
		sem_post(philo->dead);
		sem_post(philo->eat[philo->id]);
		sem_post(philo->fork);
		sem_post(philo->fork);
		ft_message(philo, "is sleeping", MAGENTA);
		ft_usleep(philo->time_to_sleep, philo);
		ft_message(philo, "is thinking", YELLOW);
    }
}
int child_process(t_philo *philo)
{
	philo->id  += 1;
	sem_unlink(ft_strjoin("sem_eat", ft_itoa(philo->id)));
	philo->eat[philo->id] = sem_open(ft_strjoin("sem_eat", ft_itoa(philo->id)), O_CREAT, 0644, 1);
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
               kill(pid[i], SIGKILL);
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
	philo->last_time_eat = philo->start_time;
    pid = malloc(sizeof(int) * philo->num_of_philos);
	i = -1;
	while (++i < philo->num_of_philos)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf(RED"Error in the fork\n"RESET));
		else if (pid[i] == 0)
		{
		  philo->id = i;
		  break;
		}
	}
	if (pid[philo->id] == 0 && !child_process(philo))
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
