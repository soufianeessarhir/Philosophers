/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:52 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:33:47 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meales_eaten(t_data *data)
{
	int	i;

	if (data->philo->num_times_to_eat == -1)
		return (0);
	i = -1;
	while (++i < data[0].num_of_philos)
		if (data->philo[i].num_times_eaten < data->philo[i].num_times_to_eat)
			return (0);
	return (1);
}

void	*a_worker(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	while (!dead_check(data->philo))
	{
		i = -1;
		while (++i < data->num_of_philos && !dead_check(data->philo))
		{
			pthread_mutex_lock(&data->time_mutex);
			if (current_time() - data->philo[i].last_time_eat
				> data->time_to_die || meales_eaten(data))
			{
				if (!meales_eaten(data))
					ft_message(&data->philo[i], "died", BOLD_RED);
				pthread_mutex_lock(&data->dead_flag_mutex);
				return (data->dead_flag = 1, pthread_mutex_unlock(
						&data->dead_flag_mutex), pthread_mutex_unlock(
						&data->time_mutex), pthread_mutex_unlock(
						data->philo[i].left_fork), NULL);
			}
			pthread_mutex_unlock(&data->time_mutex);
		}
	}
	return (NULL);
}

void	*worker(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!dead_check(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		ft_message(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(philo->right_fork);
		ft_message(philo, "has taken a fork", CYAN);
		ft_message(philo, "is eating", YELLOW);
		ft_usleep(philo->time_to_eat, philo);
		pthread_mutex_lock(philo->time_mutex);
		philo->last_time_eat = current_time();
		philo->num_times_eaten++;
		pthread_mutex_unlock(philo->time_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_message(philo, "is sleeping", MAGENTA);
		ft_usleep(philo->time_to_sleep, philo);
		ft_message(philo, "is thinking", GREEN);
	}
	return (NULL);
}

int	th_starting(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(&data->admin, NULL, a_worker, data) && data)
		return (printf(RED"Failed to create admin philosopher\n"RESET));
	while (++i < data->num_of_philos)
		if (pthread_create(&data->philo[i].thread,
				NULL, worker, &data->philo[i]))
			return (printf(RED"Failed to create philosopher number %d\n"RESET,
					i));
	pthread_join(data->admin, NULL);
	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_join(data->philo[i].thread, NULL))
			return (printf(RED"Failed to join philosopher number %d\n"RESET,
					i));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!ft_parce_args(ac, av))
			return (printf(RED"Error in the arguments. Retry again.\n"RESET));
		if (ft_atoi(av[1]) == 0 || ft_atoi(av[2]) < 60
			|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
			return (0);
		init_data(&data, ac, av);
		th_starting(&data);
		free(data.philo);
		free(data.forks);
	}
	else
		return (printf(UNDERLINE BOLD RED"Usage: %s number_of_philosophers"
				"time_to_die time_to_eat time_to_sleep"
				"[number_of_times_each_philosopher_must_eat]\n"RESET, av[0]));
	return (0);
}
