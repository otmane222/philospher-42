/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:16:27 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/19 01:41:01 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (!fa)
		return ;
	fa->diedd = 1;
	while (j < i)
	{
		data[j].philo_num = i;
		data[j].fa = fa;
		data[j].time_to_die = ft_atoi(av[2]);
		data[j].time_to_eat = ft_atoi(av[3]);
		data[j].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data[j].num_to_eat = ft_atoi(av[5]);
		else
			data[j].num_to_eat = -1;
		j++;
	}
}

void	fork_continue(t_philo *data, t_dead *dead, pid_t *arr)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		dead[i].cpid = fork();
		if (dead[i].cpid == 0)
		{
			routine(&data[i]);
			exit (0);
		}
		arr[i] = dead[i].cpid;
		dead[i].num = data->philo_num;
		i++;
	}
}

void	do_fork(t_philo *data)
{
	pthread_t		*a_th;
	t_dead			*dead;
	pid_t			*arr;
	int				i;

	i = 0;
	dead = malloc (sizeof(t_dead) * data->philo_num);
	if (!dead)
		return ;
	arr = malloc (sizeof(pid_t) * data->philo_num);
	if (!arr)
		return ;
	a_th = malloc (sizeof(pthread_t) * data->philo_num);
	if (!a_th)
		return ;
	fork_continue(data, dead, arr);
	full_dataa(dead, arr, data->philo_num);
	while (i < data->philo_num)
	{
		pthread_create(&a_th[i], NULL, &wait_pids, &dead[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
		pthread_join(a_th[i++], NULL);
}
