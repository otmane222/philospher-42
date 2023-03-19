/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:45:45 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/17 23:10:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_thread(long long n)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
	{
		usleep(500);
	}
}

void	finishing(t_philo *data, pthread_mutex_t *forks, char **av)
{
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	k = ft_atoi(av[1]);
	while (i < k)
	{
		pthread_join(data[i].a_th, NULL);
		i++;
	}
	i = 0;
	while (i < k)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	initialize(pthread_mutex_t *forks, \
							t_philo *data, char **av, pthread_mutex_t a)
{
	int		k;
	int		j;

	j = 0;
	k = ft_atoi(av[1]);
	pthread_mutex_init(&a, NULL);
	while (j < k)
	{
		pthread_mutex_init(&forks[j], NULL);
		j++;
	}
	j = 0;
	while (j < k)
	{
		data[j].id = j + 1;
		data[j].print = &a;
		data[j].left_fork = &forks[j];
		data[j].right_fork = &forks[(j + 1) % k];
		j++;
	}
}

void	khouta_b(long long t, long long t_ime2, t_philo *data)
{
	t_ime2 = get_time();
	pthread_mutex_lock(data->print);
	if ((t_ime2 - t) > data->time_to_die && data->fa->diedd)
	{
		if (data->fa->diedd == 1)
		{
			printf("%lld		%d is died\n", t_ime2 - t, data->id);
			data->fa->diedd = 0;
		}
	}
	pthread_mutex_unlock(data->print);
}
