/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:52 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:29:17 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->fork);
	ft_message(philo, "has taken a fork", CYAN);
	sem_wait(philo->fork);
	ft_message(philo, "has taken a fork", CYAN);
	ft_message(philo, "is eating", GREEN);
	ft_usleep(philo->time_to_eat, philo);
}

void	*a_worker(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->eat[philo->id]);
		sem_wait(philo->dead);
		if (current_time() - philo->last_time_eat > philo->time_to_die)
		{
			sem_wait(philo->message);
			printf("%s""%zu %d %s\n" RESET, BOLD_RED, current_time()
				- philo->start_time, philo->id, "died");
			sem_post(philo->dead);
			sem_post(philo->eat[philo->id]);
			return (free_all(philo), exit(1), (void *)0);
		}
		sem_post(philo->dead);
		sem_post(philo->eat[philo->id]);
		usleep(100);
	}
}

void	*worker(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		eat(philo);
		sem_wait(philo->eat[philo->id]);
		sem_wait(philo->dead);
		if (philo->num_times_to_eat != -1 && philo->num_times_eaten
			== philo->num_times_to_eat)
			return (free_all(philo), exit(1), (void *)0);
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

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (!ft_parce_args(ac, av))
			return (printf(RED"Error in the arguments. Retry again.\n"RESET));
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60
			|| ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 1))
			return (0);
		init_philo(&philo, ac, av);
		th_starting(&philo);
		sem_unlink("fork_sem");
		sem_unlink("dead_sem");
		sem_unlink("message_sem");
		sem_close(philo.fork);
		sem_close(philo.dead);
		sem_close(philo.message);
	}
	else
		return (printf(UNDERLINE BOLD RED"Usage: %s number_of_philosophers"
				"time_to_die time_to_eat time_to_sleep"
				"[number_of_times_each_philosopher_must_eat]\n"RESET, av[0]));
	return (0);
}
