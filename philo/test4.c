/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:49:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/08 21:21:08 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>


int	time_in_ms(struct timeval start_t, struct timeval end_t)
{
	int	x;

	x = (end_t.tv_sec - start_t.tv_sec) * 1000;
	return (x);
}

long long	get_timex(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec));
}


int main()
{
    struct timeval	tv;
	struct timeval	start_t;
	struct timeval	end_t;

    // gettimeofday(&start_t, NULL);
	// int	i = 0;
	// sleep(2);
	// gettimeofday(&end_t, NULL);
	// int dif = time_in_ms(start_t, end_t);
	// printf("%d\n", dif);
    // // printf("Seconds: %ld\n", tv.tv_sec);
    // // printf("Microseconds: %d\n", tv.tv_usec);
	// sleep(2);
	// gettimeofday(&end_t, NULL);
	// dif = time_in_ms(start_t, end_t);

	printf("%lld-----\n", dif2 - dif);

    return 0;
}
