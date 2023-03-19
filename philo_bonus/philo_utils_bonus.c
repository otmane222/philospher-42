/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:17:14 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/19 01:40:56 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	*wait_pids(void *arg)
{
	t_dead	*dead;
	int		i;

	i = 0;
	dead = (t_dead *)arg;
	waitpid(dead->cpid, NULL, 0);
	while (i < dead->num)
	{
		kill(dead->pids[i++], SIGKILL);
	}
	return (0);
}

void	full_dataa(t_dead *dead, pid_t *arr, int a)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < a)
	{
		dead[i].pids = malloc(sizeof(pid_t) * a);
		if (!dead[i].pids)
			return ;
		i++;
	}
	i = 0;
	while (i < a)
	{
		j = 0;
		while (j < a)
		{
			dead[i].pids[j] = arr[j];
			j++;
		}
		i++;
	}
}
