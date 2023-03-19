/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:19:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/19 01:41:36 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	rest_routine(long long t_ime, t_philo *data)
{
	int			i;
	long long	t_ime2;
	pid_t		*pids;

	i = 0;
	pids = malloc (sizeof(pid_t) * data->philo_num);
	if (!pids)
		return (get_time());
	sem_post(data->left_fork);
	sem_post(data->right_fork);
	t_ime2 = get_time();
	sleeping(data->id, t_ime2 - t_ime, data);
	if (data->time_to_sleep > data->time_to_die)
	{
		sleep_thread(data->time_to_die);
		sem_wait(data->print);
		printf("%lld		%d diedd\n", get_time() - t_ime, data->id);
		exit (0);
	}
	sem_post(data->print);
	sleep_thread(data->time_to_sleep);
	return (get_time());
}

long long	start_routine(long long t_ime, t_philo *data)
{
	long long	t_ime2;

	t_ime2 = get_time();
	thinking(data->id, t_ime2 - t_ime, data);
	if (data->time_to_eat > data->time_to_die && data->id % 2 != 0)
	{
		sleep_thread(data->time_to_die);
		sem_wait(data->print);
		printf("%lld		%d died\n", get_time() - t_ime, data->id);
		exit (0);
	}
	sem_wait(data->left_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	sem_wait(data->right_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	t_ime2 = get_time();
	eat(data->id, t_ime2 - t_ime, data);
	sleep_thread(data->time_to_eat);
	return (t_ime2);
}

void	khouta_b(long long t, long long t_ime2, t_philo *data)
{
	t_ime2 = get_time();
	sem_wait(data->print);
	if ((t_ime2 - t) > data->time_to_die)
	{
		printf("%lld		%d is diedf\n", t_ime2 - t, data->id);
		exit (0);
	}
	sem_post(data->print);
}

void	routine(t_philo *data)
{
	int				i;
	long long		t_ime;
	long long		t_ime2;

	t_ime = get_time();
	t_ime2 = 0;
	if (data->id % 2 == 0)
		usleep(20000);
	if (data->num_to_eat == -1)
		i = -2;
	else
		i = 0;
	while (i < data->num_to_eat)
	{
		data->t = start_routine(t_ime, data);
		data->t = rest_routine(t_ime, data);
		if (data->num_to_eat == -1)
			continue ;
		else
			i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*data;
	sem_t	*a;
	int		*v;

	v = 0;
	v = malloc(10);
	if (ac <= 4 || ac <= 3)
		return (write(2, "Wrong number of arguments\n", 26), 0);
	if (check_arg(av) == FAILURE)
		return (write(2, "Enter a corrects numbers\n", 25), 0);
	data = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data)
		return (0);
	a = malloc (sizeof(sem_t) * ft_atoi(av[1]));
	if (!a)
		return (0);
	full_data(data, av, ac);
	initialize(a, data, av);
	do_fork(data);
	return (0);
}
