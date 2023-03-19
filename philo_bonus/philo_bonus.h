/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:16:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/19 01:41:22 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define SUCESS 1
# define FAILURE 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/ipc.h>
# include <pthread.h>
# include <limits.h>
# include <signal.h>
# include <sys/shm.h>

# define SUCESS 1
# define FAILURE 0

typedef struct s_fa
{
	int				diedd;
}	t_fa;

typedef struct s_philo
{
	sem_t		*left_fork;
	sem_t		*right_fork;
	sem_t		*print;
	struct s_fa	*fa;
	pthread_t	a_th;
	int			id;
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_to_eat;
	long long	t;
	int			*died;
}	t_philo;

typedef struct s_dead
{
	pid_t	*pids;
	int		cpid;
	int		num;
}	t_dead;


int			ft_atoi(const char *str);
long long	get_time(void);
void		thinking(int n, long long dif, t_philo *data);
void		took_a_fork(int n, long long dif, t_philo *data);
void		sleeping(int n, long long dif, t_philo *data);
void		eat(int n, long long dif, t_philo *data);
long long	rest_routine(long long t_ime, t_philo *data);
long long	start_routine(long long t_ime, t_philo *data);
void		sleep_thread(long long n);
int			check_arg(char **av);
void		routine(t_philo *data);
void		initialize(sem_t *a, t_philo *data, char **av);
void		do_fork(t_philo *data);
void		full_data(t_philo *data, char **av, int ac);
void		*wait_pids(void *arg);

#endif
