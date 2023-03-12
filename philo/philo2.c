/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:00:41 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/12 20:16:44 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	khouta_b(long long t, long long t_ime2, t_philo *data)
{
	t_ime2 = get_time();
	pthread_mutex_lock(data->print);
	if ((t_ime2 - t) > (data->time_to_die / 1000))
	{
		if (data->fa->diedd == 1)
		{
			printf("%lld		%d is died\n", t_ime2 - t, data->id);
			data->fa->diedd = 0;
		}
	}
	pthread_mutex_unlock(data->print);
}

void	*routine(void *arg)
{
	t_philo			*data;
	int				i;
	long long		t_ime;
	long long		t_ime2;

	data = (t_philo *)arg;
	t_ime = get_time();
	t_ime2 = 0;
	if (data->num_to_eat == -1)
		i = -2;
	else
		i = 0;
	while (i < data->num_to_eat)
	{
		data->t = start_routine(t_ime, data);
		t_ime2 = rest_routine(t_ime, data);
		khouta_b(data->t, t_ime2, data);
		if (data->fa->diedd == 0)
			return (0);
		if (data->num_to_eat == -1)
			continue ;
		else
			i++;
	}
	return (0);
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
	fa = malloc(sizeof(t_fa));
	fa->diedd = 1;
	while (j < i)
	{
		data[j].philo_num = i;
		data[j].fa = fa;
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

int	main(int ac, char **av)
{
	t_philo			*data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	forkk;
	pthread_t		*a_th;
	int				*i;

	if (ac <= 4 || ac <= 3)
		return (write(2, "Wrong number of arguments\n", 26), 0);
	if (check_arg(av) == FAILURE)
		return (write(2, "Enter a corrects numbers\n", 25), 0);
	data = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (0);
	initialize(forks, data, av, forkk);
	full_data(data, av, ac);
	finishing(data, forks);
	free(data->fa);
	free(data);
	free(forks);
	return (0);
}
