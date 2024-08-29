/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:34:35 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:36:19 by sessarhi         ###   ########.fr       */
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

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

void	ft_message(t_philo *philo, char *text, char *color)
{
	pthread_mutex_lock(philo->message);
	if (!dead_check(philo))
		printf("%s""%zu %d %s\n" RESET, color,
			current_time() - philo->start_time, philo->id, text);
	pthread_mutex_unlock(philo->message);
}

int	ft_usleep(size_t t_ms, t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < t_ms)
	{
		if (dead_check(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	dead_check(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo->dead_flag_mutex);
		if (*philo->dead == 1)
			return (pthread_mutex_unlock(philo->dead_flag_mutex), 1);
		pthread_mutex_unlock(philo->dead_flag_mutex);
	}
	return (0);
}
