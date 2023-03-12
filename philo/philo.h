/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:12:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/12 20:15:52 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define SUCESS 1
# define FAILURE 0

typedef struct s_fa
{
	int				diedd;
}	t_fa;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	struct s_fa		*fa;
	pthread_t		a_th;
	int				id;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	long long		t;
}	t_philo;



int			ft_atoi(const char *str);
long long	get_time(void);
void		thinking(int n, long long dif, t_philo *data);
void		took_a_fork(int n, long long dif, t_philo *data);
void		sleeping(int n, long long dif, t_philo *data);
void		eat(int n, long long dif, t_philo *data);
long long	rest_routine(long long t_ime, t_philo *data);
long long	start_routine(long long t_ime, t_philo *data);
void		sleep_thread(long long t_ime, long long n);
void		finishing(t_philo *data, pthread_mutex_t *forks);
void		initialize(pthread_mutex_t *forks, \
								t_philo *data, char **av, pthread_mutex_t a);

#endif
