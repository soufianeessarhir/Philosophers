/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:02:55 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:03:23 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_unlock(data->philo[i].left_fork);
		pthread_mutex_unlock(data->philo[i].right_fork);
		pthread_mutex_destroy(data->philo[i].left_fork);
		pthread_mutex_destroy(data->philo[i].right_fork);
	}
}
