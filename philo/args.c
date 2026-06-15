/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:44:43 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/14 10:50:30 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_isdigit(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else if ((argv[i][j] == '-' || argv[i][j] == '+'))
			{
				j++;
				flag++;
			}
			else if (flag > 1)
				return (false);
			else
				return (false);
		}
		i++;
	}
	return (true);
}

bool	overflow(char **numbers)
{
	int	len;

	while (*numbers)
	{
		len = ft_strlen(*numbers);
		if (**numbers == '-')
		{
			if (len > 11)
				return (false);
			else if (len == 11 && ft_strncmp(*numbers + 1, "2147483648",
					10) > 0)
				return (false);
		}
		else
		{
			if (len > 10)
				return (false);
			else if (len == 10 && ft_strncmp(*numbers, "2147483647", 10) > 0)
				return (false);
		}
		numbers++;
	}
	return (true);
}

bool	check_args(char **argv)
{
	if (!check_isdigit(argv))
		return (false);
	if (!overflow(argv + 1))
		return (false);
	return (true);
}
