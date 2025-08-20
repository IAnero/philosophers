/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:53:12 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 12:45:07 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_validity_arg(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_is_numeric(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	init_data_routine(char *av[], t_data *info)
{
	info->philo_nbr = ft_atol(av[1]);
	info->time_to_eat = ft_atol(av[3]);
	info->time_to_die = ft_atol(av[2]);
	info->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		info->nbr_time_eat = ft_atol(av[5]);
		if (info->nbr_time_eat == 0)
			info->nbr_eat_zero = 0;
		else
			info->nbr_eat_zero = -1;
	}
	else
	{
		info->nbr_eat_zero = -1;
		info->nbr_time_eat = 0;
	}
}
