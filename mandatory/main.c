/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:49 by sessarhi          #+#    #+#             */
/*   Updated: 2024/05/16 14:43:02 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"





int main(int ac , char **av)
{
	if (ac == 6 || ac == 5)
	{
		if (!ft_parce_args(ac,av))
			return (printf("erorr in the arguments retry again\n"));
			
	}
	return (0);
}