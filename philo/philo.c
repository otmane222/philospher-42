/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:13:18 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/07 11:24:06 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


pthread_mutex_t	waitex;



void	time_in_ms(struct timeval start_t, struct timeval end_t, long long *dif)
{
	*dif = (end_t.tv_sec - start_t.tv_sec) * 1000;
}

void	eat(int n, long long dif)
{
	printf("%lldms	 	%d is eating\n", dif, n);
}

void	sleeping(int n, long long dif)
{
	printf("%lldms	 %d is sleeping\n", dif, n);
}
void	thinking(int n, long long dif)
{
	printf("%lldms	 %d is thinking\n", dif, n);
}

void	took_a_fork_l(struct timeval start_t, \
		struct timeval end_t, long long *dif, int n)
{
	time_in_ms(start_t, end_t, dif);
	printf("%lldms		%d has taken a fork left\n", *dif, n);
}

void	took_a_fork_r(struct timeval start_t, \
		struct timeval end_t, long long *dif, int n)
{
	time_in_ms(start_t, end_t, dif);
	printf("%lldms		%d has taken a fork right\n", *dif, n);
}

int	*do_something(t_philo *data)
{
	int				i;
	struct timeval	start_t[2];
	struct timeval	end_t[2];
	long long		dif;
	int				num_to_eat;

	i = 1;
	num_to_eat = data->philo_num;
	if (data->id % data->philo_num == 1)
		usleep(1000);
	gettimeofday(&start_t[0], NULL);
	while (i)
	{
		usleep(100);
		pthread_mutex_lock(data->left_fork);
		gettimeofday(&end_t[0], NULL);
		took_a_fork_l(start_t[0], end_t[0], &dif, data->id + 1);
		pthread_mutex_lock(data->right_fork);
		gettimeofday(&end_t[0], NULL);
		took_a_fork_r(start_t[0], end_t[0], &dif, data->id + 1);
		time_in_ms(start_t[0], end_t[0], &dif);
		gettimeofday(&start_t[1], NULL);
		eat(data->id + 1, dif);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		gettimeofday(&end_t[1], NULL);
		if ((end_t[1].tv_sec - start_t[1].tv_sec) * 1000 > data->time_to_die)
		{
			printf("%lldms		%d died ---%d---\n", dif, data->id, data->id);
			data->died = 1;
			return (0);
		}
		sleep(1);
		if (i == data->num_to_eat)
		{
			printf("got here\n");
			break ;
		}
		i++;
	}
	return (&data->died);
}

void	*nothing(void *arg)
{
	t_philo			*data;

	data = (t_philo *)arg;
	int *k = do_something(data);
	return (k);
}

int	main(int ac, char **av)
{
	t_philo			*data;
	pthread_mutex_t	*forks;
	pthread_t		*a_th;
	int				i;
	int				k;


	k = ft_atoi(av[1]);
	i = 0;
	data = malloc(sizeof(t_philo) * k);
	a_th = malloc(sizeof(pthread_t) * k);
	if (!a_th)
		return (0);
	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * k);
	if (!forks)
		return (0);
	pthread_mutex_init(forks, NULL);
	while (i < k)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < k)
	{
		data[i].time_to_die = ft_atoi(av[2]);
		data[i].time_to_eat = ft_atoi(av[3]);
		data[i].time_to_sleep = ft_atoi(av[4]);
		data[i].num_to_eat = ft_atoi(av[5]);
		data[i].philo_num = k;
		data[i].died = 0;
		data[i].a_th = a_th[i];
		data[i].id = i;
		data[i].left_fork = &forks[i];
		data[i].right_fork = &forks[(i + 1) % k];
		i++;
	}
	i = 0;
	while (i < k)
	{
		if (pthread_create(&a_th[i], NULL, &nothing, &data[i]) != 0)
			perror("Failed to creat thread\n");
		i++;
	}
	i = 0;
	void *res;
	while (i < k)
	{
		if (pthread_join(a_th[i], &res) != 0)
			perror("Failed to wait thread\n");
		pthread_detach(a_th[i]);
		int result = *((int *)res);
		if (result == 1)
		{
			printf("got heree\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < k)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (0);
}

/*
while (i < k)
{
	if (pthread_create(&a_th[i], NULL, &nothing, forks) != 0)
		perror("Failed to creat thread\n");
	i++;
}
while (i < k)
{
	if (pthread_join(a_th[i], NULL) != 0)
		perror("Failed to wait thread\n");
	i++;
}
while (i)
{
	gettimeofday(&end_t, NULL);
	time_in_ms(start_t, end_t, &dif);
	sleeping(data->id + 1, dif);
	usleep(data->time_to_sleep * 1000);
	pthread_mutex_lock(data->left_fork);
	gettimeofday(&end_t, NULL);
	time_in_ms(start_t, end_t, &dif);
	printf("%lldms	 %d has taken a fork\n", dif, data->id + 1);
	pthread_mutex_lock(data->right_fork);
	gettimeofday(&end_t, NULL);
	time_in_ms(start_t, end_t, &dif);
	printf("%lldms	 %d has taken a fork\n", dif, data->id + 1);
	gettimeofday(&end_t, NULL);
	time_in_ms(start_t, end_t, &dif);
	eat(data->id + 1, dif);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	gettimeofday(&end_t, NULL);
	time_in_ms(start_t, end_t, &dif);
	thinking(data->id + 1, dif);
	i++;
}
*/