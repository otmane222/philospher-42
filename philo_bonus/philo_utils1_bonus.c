/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:26:59 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/18 01:11:35 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(int n, long long dif, t_philo *data)
{
	sem_wait(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is eating\n", dif, n);
	sem_post(data->print);
}

void	sleeping(int n, long long dif, t_philo *data)
{
	sem_wait(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is sleeping\n", dif, n);
	sem_post(data->print);
}

void	thinking(int n, long long dif, t_philo *data)
{
	sem_wait(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d is thinking\n", dif, n);
	sem_post(data->print);
}

void	took_a_fork(int n, long long dif, t_philo *data)
{
	sem_wait(data->print);
	if (data->fa->diedd == 1)
		printf("%lld		%d has taken left a fork\n", dif, n);
	sem_post(data->print);
}

long long	get_time(void)
{
	struct timeval	time;
	static int		timestart;

	gettimeofday (&time, NULL);
	if (!timestart)
		timestart = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)) - timestart);
}
