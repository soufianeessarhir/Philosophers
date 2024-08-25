/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:14:17 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/25 14:30:49 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <signal.h>

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
#define BOLD_RED "\x1b[1m\x1b[31m"

typedef struct s_philo
{
	int             num_of_philos;
    pthread_t       philo;
    size_t          last_time_eat;
    int             id;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    int             num_times_eaten;
    int             num_times_to_eat;
    size_t          start_time;
	size_t          time_to_die;
	sem_t			*fork;
	sem_t			*time_sem;
	sem_t			*message;
    sem_t			*dead;
} t_philo;


int ft_parce_args(int ac, char **av);
int	ft_atoi(const char *str);
size_t	current_time(void);
int	ft_usleep(size_t t_ms, t_philo *philo);
// int dead_check(t_philo *philo);
void ft_message(t_philo *philo, char *text, char *color);
void init_philo(t_philo *philo, int ac, char **av);
#endif