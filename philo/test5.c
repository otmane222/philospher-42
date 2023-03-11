/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:25:09 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/06 22:51:21 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;
int				mails = 0;

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

int	main(void)
{
	int				i;
	pthread_t		a_th1, a_th2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&a_th1, NULL, &nothing, NULL);
	pthread_create(&a_th2, NULL, &nothing, NULL);
	i = 0;
	pthread_join(a_th1, NULL);
	pthread_join(a_th2, NULL);
	pthread_detach(a_th1);
	pthread_detach(a_th2);
	printf("%d--\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}
