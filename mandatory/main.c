/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/05/19 18:46:22 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void init_data(t_data *data,char ** av,int ac)
{
	data->philo->num_of_philos = ft_atoi(av[1]);
	data->philo->time_to_die = ft_atoi(av[2]);
	data->philo->time_to_eat = ft_atoi(av[3]);
	data->philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->philo->num_times_to_eat = ft_atoi(av[5]);
	else
		data->philo->num_times_to_eat = -1;
}
int main(int ac , char **av)
{
	t_data data;

	if (ac == 6 || ac == 5)
	{
		if (!ft_parce_args(ac,av))
			return (printf("erorr in the arguments retry again\n"));
		init_data(&data,av,ac);
			
	}
	return (0);
}