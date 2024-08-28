/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:34:35 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/28 17:39:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

void ft_message(t_philo *philo, char *text, char *color)
{
	sem_wait(philo->message);
	printf("%s""%zu %d %s\n" RESET, color,
		current_time() - philo->start_time, philo->id, text);
	sem_post(philo->message);
}

int	ft_usleep(size_t t_ms, t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < t_ms)
	{
		usleep(100);
	}
	(void)philo;
	return (0);
}

int	child_process(t_philo *philo)
{
	philo->id  += 1;
	philo->str = ft_strjoin("sem_eat", ft_itoa(philo->id));
	sem_unlink(philo->str);
	philo->eat[philo->id] = sem_open(philo->str, O_CREAT, 0644, 1);
	philo->num_times_eaten = 0;
	if (pthread_create(&philo->philo, NULL, a_worker, philo))
		return (printf(RED"Error in the thread\n"RESET), 1);
	worker(philo);
	return (free(philo->str),exit(0), 0);
}
