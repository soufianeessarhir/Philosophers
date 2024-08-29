/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:53:04 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/29 12:29:54 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	else if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_len(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[len--] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*newstr;
	char	*str;

	i = 0;
	str = (char *)s2;
	if (!s1 || !s2)
		return (NULL);
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	while (*s1)
	{
		newstr[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		newstr[i] = *s2++;
		i++;
	}
	*(newstr + i) = '\0';
	free(str);
	return (newstr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	parent_process(t_philo *philo, int *pid)
{
	int	i;
	int	status;

	i = -1;
	while (++i < philo->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->num_of_philos)
			{
				kill(pid[i], SIGKILL);
				sem_close(philo->eat[i]);
				free(philo->eat[i]);
			}
			free(philo->eat);
			return (1);
		}
	}
	return (0);
}
