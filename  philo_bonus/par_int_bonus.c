/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_int_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:26:14 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/26 17:53:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
static	int	check_dig(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
int ft_parce_args(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (!av[i])
			return (0);	
		i++;	
	}
	if (!check_dig(av))
		return 0;
	return (1);
}
void init_philo(t_philo *philo, int ac, char **av)
{
	int i;

	i = -1;
    philo->num_of_philos = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
	philo->eat = malloc(sizeof(sem_t *) * philo->num_of_philos);
	sem_unlink("fork_sem");
	sem_unlink("dead_sem");
	sem_unlink("message_sem");
    philo->fork = sem_open("fork_sem", O_CREAT, 0644, philo->num_of_philos);
    philo->message = sem_open("message_sem", O_CREAT, 0644, 1);
	philo->dead = sem_open("dead_sem", O_CREAT, 0644, 1);
	 if (philo->fork == SEM_FAILED || philo->dead == SEM_FAILED)
    {
        printf(RED"Error initializing semaphores\n"RESET);
        exit(1);
    }
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
}

