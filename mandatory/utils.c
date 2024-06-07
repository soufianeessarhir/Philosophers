/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:34:35 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/07 04:21:00 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	ft_atoi(const char *str)
{
	long long	nb;
	int			s;

	nb = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (s * nb);
}

void *s_malloc (size_t size)
{
	void *val;
	val = malloc(size);
	if (!val)
		exit(printf("malloc has been failed when it tries to alloc %zu\n size",size));
	else
		return val;	
}

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}
int	ft_usleep(size_t t_ms,t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < t_ms)
	{
		pthread_mutex_lock(&philo->data->dead_flag_mutex);
		if (philo->data->dead_flag)
		{
			pthread_mutex_unlock(&philo->data->dead_flag_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->dead_flag_mutex);
		usleep(100);
	}
	return (0);
}
void init_data(t_data *data, int ac, char **av)
{
    int i;
    int num_philos;

    i = 0;
    num_philos = atoi(av[1]);
    data->philo = malloc(sizeof(t_philo) * num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    data->num_of_philos = num_philos;
    data->time_to_die = atoi(av[2]);
    pthread_mutex_init(&data->dead_flag_mutex, NULL);

    data->dead_flag = 0;
    while (i < num_philos)
    {
        data->philo[i].id = i + 1;
        data->philo[i].num_times_to_eat = (ac == 6) ? atoi(av[5]) : -1;
        data->philo[i].time_to_eat = atoi(av[3]);
        data->philo[i].time_to_sleep = atoi(av[4]);
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % num_philos];
        data->philo[i].data = data;
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}
