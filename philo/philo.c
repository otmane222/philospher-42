/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:00:41 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/17 23:30:18 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	helpful_call(t_philo *data, int *i)
{
	if (data->num_to_eat == -1)
		*i = -2;
	else
		*i = 0;
	if (data->id % 2 == 0)
		usleep(1000);
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
	helpful_call(data, &i);
	while (i < data->num_to_eat)
	{
		data->t = start_routine(t_ime, data);
		data->t = rest_routine(t_ime, data);
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

void	full_again(t_philo *data, char **av, int i, int ac)
{
	data->philo_num = i;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_to_eat = ft_atoi(av[5]);
	else
		data->num_to_eat = -1;
}

void	full_data(t_philo *data, char **av, int ac)
{
	int		i;
	int		j;
	t_fa	*fa;

	j = 0;
	i = ft_atoi(av[1]);
	fa = malloc(sizeof(t_fa));
	if (!fa)
		return ;
	fa->diedd = 1;
	if (i == 1)
	{
		philo_one(av);
		data[j].fa = fa;
		return ;
	}
	while (j < i)
	{
		full_again(&data[j], av, i, ac);
		data[j].fa = fa;
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

	if (ac <= 4 || ac <= 3)
		return (write(2, "Wrong number of arguments\n", 26), 0);
	if (check_arg(av) == FAILURE)
		return (write(2, "Enter a corrects numbers\n", 25), 0);
	if (ft_atoi(av[1]) == 0)
		return (1);
	data = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (1);
	pthread_mutex_init(&forkk, NULL);
	initialize(forks, data, av, forkk);
	full_data(data, av, ac);
	finishing(data, forks, av);
	free_mem(data, forks);
	pthread_mutex_destroy(&forkk);
	return (0);
}
