/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:06:14 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/12 19:06:24 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(int n, long long dif, t_philo *data)
{
	pthread_mutex_lock(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is eating\n", dif, n);
	pthread_mutex_unlock(data->print);
}

void	sleeping(int n, long long dif, t_philo *data)
{
	pthread_mutex_lock(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is sleeping\n", dif, n);
	pthread_mutex_unlock(data->print);
}

void	thinking(int n, long long dif, t_philo *data)
{
	pthread_mutex_lock(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is thinking\n", dif, n);
	pthread_mutex_unlock(data->print);
}

void	took_a_fork(int n, long long dif, t_philo *data)
{
	pthread_mutex_lock(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d has taken left a fork\n", dif, n);
	pthread_mutex_unlock(data->print);
}

long long	get_time(void)
{
	struct timeval	time;
	static int		timestart;

	gettimeofday (&time, NULL);
	if (!timestart)
		timestart = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)) - timestart );
}
