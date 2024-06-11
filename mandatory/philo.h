/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:23:53 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/11 10:47:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"
#define REVERSE "\033[7m"

typedef struct s_data t_data;
typedef struct s_philo
{
    int             dead;
    pthread_t       thread;
    size_t          last_time_eat;
    int             id;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    int             num_times_to_eat;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
} t_philo;

typedef struct s_data
{
	pthread_mutex_t	time_mutex;
	pthread_mutex_t message;
	int 			counter;
    int             dead_flag;
    size_t          start_time;
    int             num_of_philos;
    pthread_t       admin;
    size_t          time_to_die;
    t_philo         *philo;
    pthread_mutex_t *forks;
    pthread_mutex_t dead_flag_mutex;
} t_data;


int ft_parce_args(int ac, char **av);
int	ft_atoi(const char *str);
void *s_malloc (size_t size);
size_t	current_time(void);
int	ft_usleep(size_t t_ms);
void init_data(t_data *data, int ac, char **av);
void ft_message(t_philo *philo, char *text, char *color);

#endif