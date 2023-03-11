/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:00:41 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/10 23:53:38 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define SUCESS 1
#define FAILURE 0

int		m = 0;

void	eat(int n, long long dif, t_philo *data)
{
	if (data->death == 0)
		printf("%lld		%d is eating\n", dif, n);
}

void	sleeping(int n, long long dif, t_philo *data)
{
	if (data->death == 0)
		printf("%lld		%d is sleeping\n", dif, n);
}

void	thinking(int n, long long dif, t_philo *data)
{
	if (data->death == 0)
		printf("%lld		%d is thinking\n", dif, n);
}

void	took_a_fork(int n, long long dif, t_philo *data)
{
	if (data->death == 0)
		printf("%lld		%d has taken left a fork\n", dif, n);
}

long long	get_time(void)
{
	struct timeval	time;
	static int timestart;
	gettimeofday(&time, NULL);
	if(!timestart)
	{
		timestart = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	}

	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001))- timestart );
}

long long	rest_routine(long long t_ime, t_philo *data)
{
	long long	t_ime2;

	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	t_ime2 = get_time();
	sleeping(data->id, t_ime2 - t_ime, data);
	usleep(data->time_to_sleep);
	t_ime2 = get_time();
	thinking(data->id, t_ime2 - t_ime, data);
	usleep(data->time_to_sleep);
	return (get_time());
}

long long	start_routine(long long t_ime, t_philo *data)
{
	long long	t_ime2;

	if ((data->id % data->philo_num) == 0)
		usleep(100);
	pthread_mutex_lock(data->left_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	pthread_mutex_lock(data->right_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	t_ime2 = get_time();
	eat(data->id, t_ime2 - t_ime, data);
	usleep(data->time_to_eat);
	return (t_ime2);
}

int	khouta_b(long long t, long long t_ime2, t_philo *data)
{
	t_ime2 = get_time();
	if ((t_ime2 - t) > data->time_to_die / 1000)
	{
		if (data->death == 0)
			printf("%lld		%d is died\n", t_ime2 - t, data->id);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo			*data;
	t_fa			*fa;
	int				i;
	long long		t_ime;
	long long		t_ime2;
	long long		t;

	data = (t_philo *)arg;
	t_ime = get_time();
	t_ime2 = 0;
	if (data->num_to_eat == -1)
		i = -2;
	else
		i = 0;
	while (i < data->num_to_eat)
	{
		t = start_routine(t_ime, data);
		t_ime2 = rest_routine(t_ime, data);
		data->died = khouta_b(t_ime, t_ime2, data);
		if (data->died == 0)
		{
			data->death = 1;
			return (0);
		}
		if (data->num_to_eat == -1)
			continue ;
		else
			i++;
	}
	return ((void *)1);
}

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

void	full_data(t_philo *data, char **av, int ac)
{
	int		i;
	int		j;
	t_fa	*fa;

	j = 0;
	i = ft_atoi(av[1]);
	fa = data->fa;
	while (j < i)
	{
		data[j].philo_num = i;
		data[j].time_to_die = ft_atoi(av[2]) * 1000;
		data[j].time_to_eat = ft_atoi(av[3]) * 1000;
		data[j].time_to_sleep = ft_atoi(av[4]) * 1000;
		if (ac == 6)
			data[j].num_to_eat = ft_atoi(av[5]);
		else
			data[j].num_to_eat = -1;
		if (pthread_create(&data[j].a_th, NULL, &routine, &data[j]) != 0)
			printf("Error creating thread\n");
		j++;
	}
}

void	initialize(pthread_mutex_t *forks, t_philo *data, char **av, int *m)
{
	int		k;
	int		j;

	j = 0;
	k = ft_atoi(av[1]);
	pthread_mutex_init(forks, NULL);
	// pthread_mutex_init(&data->print, NULL);
	while (j < k)
	{
		pthread_mutex_init(&forks[j], NULL);
		j++;
	}
	j = 0;
	while (j < k)
	{
		data[j].id = j + 1;
		data[j].death = m;
		data[j].left_fork = &forks[j];
		data[j].right_fork = &forks[(j + 1) % k];
		j++;
	}
}

void	finishing(t_philo *data, pthread_mutex_t *forks)
{
	int		i;
	int		k;
	int		j;
	void	*res;

	i = 0;
	j = 0;
	k = data[i].philo_num;
	while (i < k)
	{
		pthread_join(data[i].a_th, res);
		if (((int *)res) == 0)
		{
			break ;
		}
		i++;
	}
	i = 0;
	while (i < k)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*data;
	pthread_mutex_t	*forks;
	pthread_t		*a_th;
	int				*i;

	if (ac <= 4 || ac <= 3)
		return (write(2, "Wrong number of arguments\n", 26), 0);
	if (check_arg(av) == FAILURE)
		return (write(2, "Enter a corrects numbers\n", 25), 0);
	data = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data)
		return (0);
	data->fa = malloc(sizeof(t_fa) * ft_atoi(av[1]));
	if (!data->fa)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (0);
	initialize(forks, data, av, i);
	full_data(data, av, ac);
	finishing(data, forks);



	return (0);
}
