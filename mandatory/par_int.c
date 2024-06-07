/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:26:14 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/07 06:58:11 by sessarhi         ###   ########.fr       */
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
int ft_parce_args(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (!av[i])
			return (0);	
		i++;	
	}
	if (!check_dig(av))
		return 0;
	return (1);
}
void init_data(t_data *data, int ac, char **av)
{
    data->counter = 0;
    data->num_of_philos = atoi(av[1]);
    data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    data->time_to_die = atoi(av[2]);
    pthread_mutex_init(&data->dead_flag_mutex, NULL);
	data->start_time = current_time();
    data->dead_flag = 0;
	pthread_mutex_init(&data->message,NULL);
    while (data->counter < data->num_of_philos)
    {
        data->philo[data->counter].id = data->counter + 1;
        data->philo[data->counter].num_times_to_eat = (ac == 6) ? atoi(av[5]) : -1;
        data->philo[data->counter].time_to_eat = atoi(av[3]);
        data->philo[data->counter].time_to_sleep = atoi(av[4]);
        data->philo[data->counter].left_fork = &data->forks[data->counter];
        data->philo[data->counter].right_fork = &data->forks[(data->counter + 1) % data->num_of_philos];
        data->philo[data->counter].data = data;
        pthread_mutex_init(&data->forks[data->counter], NULL);
        data->counter++;
    }
}

