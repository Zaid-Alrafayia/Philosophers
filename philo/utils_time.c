/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:48:33 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/15 18:12:46 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	ft_usleep(t_table *table, long time_in_ms)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_in_ms)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead_flag)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->dead_mutex);
		usleep(1000);
	}
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000LL + (tv.tv_usec / 1000));
}

static char	*log_message(enum e_log log)
{
	if (log == EAT)
		return ("is eating");
	else if (log == SLEEP)
		return ("is sleeping");
	else if (log == THINK)
		return ("is thinking");
	else if (log == TAKEN_FORK)
		return ("has taken a fork");
	else if (log == DIED)
		return ("died");
	return ("");
}

void	print_log(t_table *table, int philo_id, enum e_log log)
{
	long long	current_time;

	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead_flag && log != DIED)
	{
		pthread_mutex_unlock(&table->print_mutex);
		pthread_mutex_unlock(&table->dead_mutex);
		return ;
	}
	current_time = get_current_time();
	printf("%lld %d %s\n", (current_time - table->start_time), philo_id,
		log_message(log));
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_unlock(&table->dead_mutex);
}
