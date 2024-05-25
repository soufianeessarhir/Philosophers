/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/05/25 02:45:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *monitor(void *lol)
{
	printf("LOL\n");
	sleep(2);
	return NULL;
}
void th_starting(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo[i].num_of_philos)
	{
		if (pthread_create(&data->philo[i].thread,NULL,monitor,data))
			exit(printf("faile to creat philo number %d\n",i));
		i++;
	}
	i = 0;
	while (i < data->philo[i].num_of_philos)
	{
		if (pthread_join(data->philo[i].thread,NULL))
			exit(printf("faile to join philo number %d\n",i));
		i++;
	}
	
	
}
void init_data(t_data *data,char **av,int ac)
{
	int i;
	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(av[1]));
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