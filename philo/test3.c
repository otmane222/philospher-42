/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:03:36 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/03 15:07:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	primes[10] = {12,34,75,2,32,53,6,78,23,1};

void	*rolle(void *arg)
{
	int	index = *(int *)arg;
	int	sum = 0;

	for (size_t i = 0; i < 5; i++)
	{
		sum += primes[index + i];
	}
	*(int *)arg = sum;
	return (arg);
}

int	main(void)
{
	pthread_t th[2];
	for (int i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));

		*a = i * 5;
		if (pthread_create(&th[i], NULL, &rolle, a) != 0)
			perror("Error creating thread");
	}
	int global = 0;
	for	(int i = 0; i < 2; i++)
	{
		int	*res;
		
		if (pthread_join(th[i], (void **) &res) != 0)
			perror("Error waiting for a thread");
		global += *res;
		free(res);
	}
	printf("sum: %d ", global);
	return (0);
}
