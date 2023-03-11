/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:18:43 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/06 22:41:23 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mails = 0;
pthread_mutex_t mutex;

void	*nothing(void *arg)
{
	for (size_t i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

void	lk(void)
{
	system("leaks a.out");
}

int	main(void)
{
	pthread_t	t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &nothing, NULL) != 0)
		write (2, "Failed to creat thread", 22);
	if (pthread_create(&t2, NULL, &nothing, NULL) != 0)
		write (2, "Failed to creat thread", 22);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%d", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}
