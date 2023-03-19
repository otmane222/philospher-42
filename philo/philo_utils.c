/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:26:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/17 03:47:21 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handler_long_atoi(long long int n, long long int o)
{
	if ((n / 10) == o)
		return (0);
	return (1);
}

static int	rtn_atoi(long long int res, int sign, const char *str)
{
	long long int	old_res;

	while (*str >= '0' && *str <= '9')
	{
		old_res = res;
		res = res * 10 + (*str - '0');
		if (handler_long_atoi(res, old_res) == 0)
			str++;
		else if (handler_long_atoi(res, old_res) == 1)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	long long int		res;
	int					sign;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	return (rtn_atoi(res, sign, str) * sign);
}

long long	rest_routine(long long t_ime, t_philo *data)
{
	long long	t_ime2;

	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	t_ime2 = get_time();
	sleeping(data->id, t_ime2 - t_ime, data);
	if (data->time_to_sleep > data->time_to_die && data->fa->diedd)
	{
		sleep_thread(data->time_to_die);
		pthread_mutex_lock(data->print);
		if (data->fa->diedd)
			printf("%lld		%d died\n", get_time() - t_ime, data->id);
		data->fa->diedd = 0;
		pthread_mutex_unlock(data->print);
	}
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
		pthread_mutex_lock(data->print);
		if (data->fa->diedd)
			printf("%lld		%d died\n", get_time() - t_ime, data->id);
		data->fa->diedd = 0;
		pthread_mutex_unlock(data->print);
	}
	pthread_mutex_lock(data->left_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	pthread_mutex_lock(data->right_fork);
	t_ime2 = get_time();
	took_a_fork(data->id, t_ime2 - t_ime, data);
	t_ime2 = get_time();
	eat(data->id, t_ime2 - t_ime, data);
	sleep_thread(data->time_to_eat);
	return (t_ime2);
}
