/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:08:18 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/07 15:51:48 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_atoi(const char *nptr)
{
	int			i;
	uint64_t	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	char	*copy;

	copy = s;
	while (n--)
		*copy++ = '\0';
}

uint64_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		printf ("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;
	uint64_t	now;

	start = get_current_time();
	while (1)
	{
		now = get_current_time();
		if (now - start >= time)
			break ;
		usleep(1);
	}
}

// int	ft_usleep(size_t ms)
// {
// 	uint64_t	start;

// 	start = get_current_time();
// 	while ((get_current_time() - start) < ms)
// 		usleep(ms / 10);
// 	return (0);	
// }


// void	existence(t_thinker *thinker)
// {
// 	while (1)
// 	{	
// 		pthread_mutex_lock(&thinker->table->key);
// 		if (thinker->table->dead)
// 		{
// 			pthread_mutex_unlock(&thinker->table->key);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&thinker->table->key);
// 		pick_up_forks(thinker);
// 		eat(thinker);
// 		put_down_forks(thinker);
// 		sleep_time(thinker->table->time_to_sleep);
// 		log_action(thinker, THINK);
// 	}
// }