/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:26:14 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:38:44 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	check_dig(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_parce_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!av[i])
			return (0);
		i++;
	}
	if (!check_dig(av))
		return (0);
	return (1);
}

void	init_data_hellper(t_data *data, int ac, char **av)
{
	data->philo[data->counter].num_times_eaten = 0;
	data->philo[data->counter].dead_flag_mutex = &data->dead_flag_mutex;
	data->philo[data->counter].time_mutex = &data->time_mutex;
	data->philo[data->counter].message = &data->message;
	data->philo[data->counter].dead = &data->dead_flag;
	data->philo[data->counter].num_of_philos = data->num_of_philos;
	data->philo[data->counter].time_to_eat = ft_atoi(av[3]);
	data->philo[data->counter].time_to_sleep = ft_atoi(av[4]);
	data->philo[data->counter].start_time = current_time();
	data->philo[data->counter].last_time_eat = current_time();
	data->philo[data->counter].left_fork = &data->forks[data->counter];
	data->philo[data->counter].right_fork
		= &data->forks[(data->counter + 1) % data->num_of_philos];
	(void)ac;
}

void	init_data(t_data *data, int ac, char **av)
{
	data->counter = -1;
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	data->dead_flag = 0;
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->message, NULL);
	pthread_mutex_init(&data->dead_flag_mutex, NULL);
	while (++data->counter < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[data->counter], NULL);
		data->philo[data->counter].id = data->counter + 1;
		if (ac == 6)
			data->philo[data->counter].num_times_to_eat = ft_atoi(av[5]);
		else
			data->philo[data->counter].num_times_to_eat = -1;
		init_data_hellper(data, ac, av);
	}
}
