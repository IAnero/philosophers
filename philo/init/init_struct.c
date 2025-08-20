/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:45:40 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/09 16:16:37 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	struct_init(t_data *info)
{
	info->philo_nbr = 0;
	info->time_to_eat = 0;
	info->time_to_die = 0;
	info->time_to_sleep = 0;
	info->nbr_time_eat = 0;
	info->start_simulation = 0;
	info->end_simulation = false;
	info->philo = NULL;
	pthread_mutex_init(&info->mtx_info, NULL);
}
