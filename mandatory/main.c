/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/03 00:29:54 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *worker(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		printf("Philosopher %d is thinking\n",data->philo->id);
		if (data->philo->id % 2 == 0)
		{
			pthread_mutex_lock(&data->forks[data->philo->id]);
			printf("Philosopher %d has taken the left fork\n",data->philo->id);
			pthread_mutex_lock(&data->forks[(data->philo->id + 1) % data->philo->num_of_philos]);
			printf("Philosopher %d has taken the right fork\n",data->philo->id);
		}
		else
		{
			pthread_mutex_lock(&data->forks[(data->philo->id + 1) % data->philo->num_of_philos]);
			printf("Philosopher %d has taken the right fork\n",data->philo->id);
			pthread_mutex_lock(&data->forks[data->philo->id]);
			printf("Philosopher %d has taken the left fork\n",data->philo->id);
		}
		pthread_mutex_unlock(&data->forks[data->philo->id]);
		pthread_mutex_unlock(&data->forks[(data->philo->id + 1) % data->philo->num_of_philos]);

		
	}

	return NULL;
}
int th_starting(t_data *data)
{
	data->philo->id = 0;
	while (data->philo->id  < data->philo->num_of_philos)
	{
		if (pthread_create(&data->philo[data->philo->id].thread,NULL,worker,data))
			return (printf("faile to creat philo number %d\n",data->philo->id));
		printf("%d\n",data->philo->id );
		data->philo->id += 1;
	}
	data->philo->id  = 0;
	while (data->philo->id  < data->philo[data->philo->id].num_of_philos)
	{
		if (pthread_join(data->philo[data->philo->id ].thread,NULL))
			return (printf("faile to join philo number %d\n",data->philo->id));
		data->philo->id += 1;
	}
	return 0;
}
void init_data(t_data *data,char **av,int ac)
{
	int i;
	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(av[1]));
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		
		data->philo[i].num_of_philos = atoi(av[1]);
		data->philo[i].time_to_die = atoi(av[2]);
		data->philo[i].time_to_eat = atoi(av[3]);
		data->philo[i].time_to_sleep = atoi(av[4]);
		if (ac == 6)
			data->philo[i].num_times_to_eat = atoi(av[5]);
		else
			data->philo[i].num_times_to_eat = -1;
		i++;
	}
		
}
int main(int ac , char **av)
{
	t_data data;

	if (ac == 6 || ac == 5)
	{
		if (!ft_parce_args(ac,av))
			return (printf("erorr in the arguments retry again\n"));
		init_data(&data,av,ac);
		th_starting(&data);	
	}
	return (0);
}