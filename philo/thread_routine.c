/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:24:13 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/18 16:08:33 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static bool	simulation_finished(t_table *table)
{
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead_flag == true)
	{
		pthread_mutex_unlock(&table->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->dead_mutex);
	return (false);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	int		max_meals;

	philo = (t_philo *)data;
	max_meals = philo->table->max_meals;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!simulation_finished(philo->table))
	{
		eating(philo);
		if (max_meals > 0 && philo->meals_counter >= max_meals)
		{
			pthread_mutex_lock(&philo->table->meals_mutex);
			philo->full = true;
			pthread_mutex_unlock(&philo->table->meals_mutex);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
