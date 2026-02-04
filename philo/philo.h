/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:09:57 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/02/04 13:14:22 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	int				*i;
	pthread_mutex_t	mutex;
}					t_mutex;

typedef struct s_philo_data
{
	int				number_of_philosphers;
	int				time_to_die;
	int				time_to_sleep;
	bool			optional;
	int				number_of_times_each_philosopher_must_eat;
}					t_philo_data;
//----------------------------------------------------//

int					ft_atoi(const char *str);

#endif // !DEBUG
