/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:21:48 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/15 15:08:46 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
//-----------------------------------structs---------------------------------//
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meals;
	long				start_time;
	bool				dead_flag;
	bool				all_full;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		meals_mutex;
};

enum					e_log
{
	EAT,
	SLEEP,
	THINK,
	TAKEN_FORK,
	DIED,
};
//----------------------------------------------------------------------------//
int						ft_atoi(const char *str);
int						ft_isdigit(int letter);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
void					error_exit(char *str);
bool					check_args(char **argv);
void					free_table(t_table *table);
void					ft_usleep(t_table *table, long time_in_ms);
long long				get_current_time(void);
void					data_init(t_table *table, int argc, char **argv);
void					print_log(t_table *table, int philo_id, enum e_log log);
void					thinking(t_philo *philos);
void					sleeping(t_philo *philos);
void					eating(t_philo *philos);
void					*philo_routine(void *data);
void					check_one_philo(t_table *table);
void					start_simulation(t_table *table);

#endif // !PHILO_H
