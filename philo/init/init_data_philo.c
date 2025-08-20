/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 07:43:01 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 16:22:14 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philo	*init_philos(int id, t_data *info)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo));
	if (!philos)
		return (NULL);
	philos->next = NULL;
	philos->id = id;
	philos->meal_count = 0;
	philos->time_last_meal = 0;
	philos->time_last_meal_by_monitor = 0;
	philos->info = info;
	philos->has_fork = false;
	philos->is_maxmeal_reached = false;
	pthread_mutex_init(&philos->mtx_meal, NULL);
	pthread_mutex_init(&philos->fork, NULL);
	if ((id % 2 != 0) && id != info->philo_nbr)
		philos->state = EATING;
	else
		philos->state = THINKING;
	return (philos);
}

void	add_back(t_philo **p, t_philo *new_p)
{
	t_philo	*tmp;

	if (*p == NULL)
		*p = new_p;
	else
	{
		tmp = *p;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_p;
	}
}
