/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:34:08 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/15 17:30:20 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_table *table, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].full = false;
		philos[i].last_meal_time = 0;
		philos[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		philos[i].left_fork = &table->forks[i];
		philos[i].table = table;
	}
}

void	init_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->dead_flag = false;
	table->all_full = false;
}

void	data_init(t_table *table, int argc, char **argv)
{
	int	i;

	i = -1;
	init_table(table, argc, argv);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		error_exit("error in malloc!");
	table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
	{
		free(table->philos);
		error_exit("error in malloc!");
	}
	while (++i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->forks[i].id = i;
	}
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->meals_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	init_philos(table, table->philos);
}
