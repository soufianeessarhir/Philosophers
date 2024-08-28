/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:16 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/28 17:41:35 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_philo *philo)
{
	int i;

	i = -1;
	sem_close(philo->eat[i]);
	sem_unlink(philo->str);
	free(philo->str);
	free(philo->eat);
}
int	th_starting(t_philo *philo) 
{
	int	i;
	int	*pid;

	philo->start_time = current_time();
	philo->last_time_eat = philo->start_time;
	pid = malloc(sizeof(int) * philo->num_of_philos);
	if (!pid)
		return (free(philo->eat), free(pid),
			exit(printf(RED"Error malloc\n"RESET)), 1);
	i = -1;
	while (++i < philo->num_of_philos)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf(RED"Error in the fork\n"RESET));
		else if (pid[i] == 0)
		{
			philo->id = i;
			break ;
		}
	}
	if (pid[philo->id] == 0 && !child_process(philo))
		return (1);
	else
		parent_process(philo, pid);
	return (free(pid), 0);
}
