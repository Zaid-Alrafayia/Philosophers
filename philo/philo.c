/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:26:36 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/18 16:50:54 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

bool	check_full(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_philos)
	{
		pthread_mutex_lock(&philo[i].table->meals_mutex);
		if (!philo[i].full)
		{
			pthread_mutex_unlock(&philo[i].table->meals_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].table->meals_mutex);
		i++;
	}
	return (true);
}

static bool	check_philo_dead(t_table *table, int i)
{
	long long	last_meal;

	pthread_mutex_lock(&table->meals_mutex);
	last_meal = table->philos[i].last_meal_time;
	pthread_mutex_unlock(&table->meals_mutex);
	if ((get_current_time() - last_meal) > table->time_to_die)
	{
		pthread_mutex_lock(&table->dead_mutex);
		table->dead_flag = true;
		pthread_mutex_unlock(&table->dead_mutex);
		print_log(table, table->philos[i].id, DIED);
		return (true);
	}
	return (false);
}

void	check_starvation(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == table->num_philos)
			i = 0;
		if (check_philo_dead(table, i))
			return ;
		if (table->max_meals > 0 && !table->all_full
			&& check_full(table->philos))
		{
			table->all_full = true;
			return ;
		}
		usleep(500);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	int		i;

	if (argc != 5 && argc != 6)
		error_exit("format must be: ./philo 5 100 200 300 [5]");
	if (!check_args(argv))
		error_exit("invalid arguments!");
	table = malloc(sizeof(t_table));
	if (!table)
		error_exit("failed to allocate memory for table");
	data_init(table, argc, argv);
	table->start_time = get_current_time();
	if (table->num_philos == 1)
		check_one_philo(table);
	start_simulation(table);
	check_starvation(table);
	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread, NULL);
	free_table(table);
	free(table);
	return (0);
}
