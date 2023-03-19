/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:27:52 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/18 00:48:07 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_thread(long long n)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
	{
		usleep(100);
	}
}

void	finishing(t_philo *data, pthread_mutex_t *forks)
{
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	k = data[i].philo_num;
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

void	one_philo(t_philo *data)
{
	int		i;

	i = 0;
	printf("0		1 has taken a fork\n");
	sleep_thread(data[i].time_to_die);
	printf("%d		1 died", data[i].time_to_die);
	exit (0);
}

void	full_rest(t_philo *data, char **av, sem_t *a, sem_t *c)
{
	int	*g;
	int	j;
	int	k;

	j = 0;
	g = malloc(10);
	if (!g)
		return ;
	*g = 1;
	k = ft_atoi(av[1]);
	while (j < k)
	{
		data[j].id = j + 1;
		data[j].print = c;
		data[j].died = g;
		data[j].left_fork = a;
		data[j].right_fork = a;
		j++;
	}
}

void	initialize(sem_t *a, t_philo *data, char **av)
{
	int		k;
	int		j;
	sem_t	*c;

	j = 0;
	k = ft_atoi(av[1]);
	if (k == 1)
		one_philo(data);
	sem_unlink("forks");
	sem_unlink("print");
	c = malloc(sizeof(sem_t) * k);
	if (!c)
		return ;
	a = sem_open("forks", O_CREAT, 0644, k);
	c = sem_open("print", O_CREAT, 0644, 1);
	if (a == SEM_FAILED)
	{
		printf("Error sem_open failed\n");
		exit (1);
	}
	j = 0;
	full_rest(data, av, a, c);
}
