/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 04:42:15 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/18 16:03:45 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(&philos->right_fork->mutex);
		print_log(philos->table, philos->id, TAKEN_FORK);
		pthread_mutex_lock(&philos->left_fork->mutex);
		print_log(philos->table, philos->id, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(&philos->left_fork->mutex);
		print_log(philos->table, philos->id, TAKEN_FORK);
		pthread_mutex_lock(&philos->right_fork->mutex);
		print_log(philos->table, philos->id, TAKEN_FORK);
	}
}

static void	unlock_forks(t_philo *philos)
{
	pthread_mutex_unlock(&philos->left_fork->mutex);
	pthread_mutex_unlock(&philos->right_fork->mutex);
}

void	eating(t_philo *philos)
{
	lock_forks(philos);
	pthread_mutex_lock(&philos->table->meals_mutex);
	print_log(philos->table, philos->id, EAT);
	philos->last_meal_time = get_current_time();
	philos->meals_counter++;
	pthread_mutex_unlock(&philos->table->meals_mutex);
	ft_usleep(philos->table, philos->table->time_to_eat);
	unlock_forks(philos);
}

void	sleeping(t_philo *philos)
{
	print_log(philos->table, philos->id, SLEEP);
	ft_usleep(philos->table, philos->table->time_to_sleep);
}

void	thinking(t_philo *philos)
{
	long	think_time;

	print_log(philos->table, philos->id, THINK);
	if (philos->table->num_philos % 2 != 0)
	{
		think_time = (philos->table->time_to_eat * 2)
			- philos->table->time_to_sleep;
		if (think_time > 0)
			ft_usleep(philos->table, think_time / 2);
	}
}
