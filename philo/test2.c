/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:25:30 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/03 10:56:53 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rolle(void *arg)
{
	int	i;
	int	*res = malloc(sizeof(int));

	i = (rand() % 6 + 1);
	*res = i;
	return ((void *) res);
}

int	main(void)
{
	int *res;
	srand(time(NULL));
	pthread_t	th;

	if (pthread_create(&th, NULL, &rolle, NULL) != 0)
		perror("Error creat thread");
	if (pthread_join(th, (void **) &res) != 0)
		perror("Error waiting thread");
	printf("Resault: %d\n", *res);
	free(res);
	return (0);
}
