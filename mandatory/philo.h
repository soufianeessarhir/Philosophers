/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:23:53 by sessarhi          #+#    #+#             */
/*   Updated: 2024/05/16 15:17:08 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	// pthread_mutex_t	*r_fork;
	// pthread_mutex_t	*l_fork;
	// pthread_mutex_t	*write_lock;
	// pthread_mutex_t	*dead_lock;
	// pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct data
{
	
	
}t_data;


int ft_parce_args(int ac, char **av);


#endif