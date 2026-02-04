/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:08:27 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/02/04 13:30:10 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_mutex	*mutex;

	mutex = (t_mutex *)args;
	pthread_mutex_lock(&mutex->mutex);
	if (!mutex->i)
		return (0);
	while (*mutex->i < 100000)
	{
		(*mutex->i)++;
	}
	pthread_mutex_unlock(&mutex->mutex);
	return (NULL);
}

t_philo_data	*init_data(int argc, char **argv, t_mutex *mutex)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
	{
		free(mutex->i);
		free(mutex);
		return (NULL);
	}
	data->number_of_philosphers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
	{
		data->optional = true;
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[4]);
	}
	else
	{
		data->optional = false;
		data->number_of_times_each_philosopher_must_eat = -1;
	}
	return (data);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_mutex			*mutex;
	t_philo_data	*data;
	int				i;

	i = 0;
	if (argc != 4 && argc != 5)
		return (0);
	mutex = malloc(sizeof(t_mutex));
	if (!mutex)
		return (0);
	mutex->i = malloc(sizeof(int));
	if (!mutex->i)
	{
		free(mutex);
		return (0);
	}
	data = init_data(argc, argv, mutex);
	if (!data)
		return (0);
	threads = malloc(data->number_of_philosphers * sizeof(pthread_t));
	if (!threads)
	{
		free(data);
		free(mutex->i);
		free(mutex);
		return (0);
	}
	pthread_mutex_init(&mutex->mutex, NULL);
	*mutex->i = 0;
	while (i < data->number_of_philosphers)
	{
		if (pthread_create(threads + i, NULL, &routine, (void *)mutex) != 0)
		{
			perror("pthread_create\n");
			return (1);
		}
		pthread_join(*(threads + i), NULL);
		i++;
	}
	printf("%d\n", *mutex->i);
	pthread_mutex_destroy(&mutex->mutex);
	free(mutex->i);
	free(mutex);
	free(threads);
	free(data);
	return (0);
}
