/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:26:36 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/16 17:27:31 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static void	check_one_philo(t_table *table)
{
	print_log(table, 1, TAKEN_FORK);
	ft_usleep(table, table->time_to_die);
	print_log(table, 1, DIED);
	exit(1);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, philo_routine,
			&table->philos[i]);
		table->philos[i].last_meal_time = table->start_time;
		i++;
	}
}

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

void	check_starvation(t_table *table)
{
	int			i;
	long long	last_meal;

	i = 0;
	while (1)
	{
		if (i == table->num_philos)
			i = 0;
		pthread_mutex_lock(&table->meals_mutex);
		last_meal = table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->meals_mutex);
		if ((get_current_time() - last_meal) > table->time_to_die)
		{
			pthread_mutex_lock(&table->dead_mutex);
			table->dead_flag = true;
			pthread_mutex_unlock(&table->dead_mutex);
			print_log(table, table->philos[i].id, DIED);
			return ;
		}
		if (table->max_meals > 0 && !table->all_full)
		{
			if (check_full(table->philos))
			{
				table->all_full = true;
				return ;
			}
		}
		ft_usleep(table, 100);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	int		i;

	i = 0;
	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv))
		{
			error_exit("invalid arguments!");
		}
		table = malloc(sizeof(t_table));
		if (!table)
			error_exit("failed to allocate memory for table");
		data_init(table, argc, argv);
		table->start_time = get_current_time();
		if (table->num_philos == 1)
			check_one_philo(table);
		start_simulation(table);
		check_starvation(table);
		while (i < table->num_philos)
		{
			pthread_join(table->philos[i].thread, NULL);
			i++;
		}
		free_table(table);
		free(table);
	}
	else
		error_exit("format must be: ./philo 5 100 200 300 [5]");
	return (0);
}
