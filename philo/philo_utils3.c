/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:02:46 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/17 23:27:39 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (FAILURE);
			i++;
		}
		j++;
	}
	return (SUCESS);
}

void	philo_one(char **av)
{
	printf("0		1 has taken a fork\n");
	sleep_thread(ft_atoi(av[2]));
	printf("%d		1 died\n", ft_atoi(av[2]));
}

void	free_mem(t_philo *data, pthread_mutex_t *forks)
{
	free(data->fa);
	free(data);
	free(forks);
}
