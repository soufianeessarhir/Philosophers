/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:34:35 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/09 02:11:26 by sessarhi         ###   ########.fr       */
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

void *s_malloc (size_t size)
{
	void *val;
	val = malloc(size);
	if (!val)
		exit(printf("malloc has been failed when it tries to alloc %zu\n size",size));
	else
		return val;	
}

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}
int	ft_usleep(size_t t_ms,t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < t_ms)
	{
		pthread_mutex_lock(&philo->data->dead_flag_mutex);
		if (philo->data->dead_flag)
		{
			pthread_mutex_unlock(&philo->data->dead_flag_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->dead_flag_mutex);
		usleep(100);
	}
	return (0);
}

