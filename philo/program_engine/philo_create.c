/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:35 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/09 16:09:43 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	create(t_data *info, t_philo *p)
{
	pthread_t	guard;
	t_philo		*current;
	int			count;

	current = p;
	count = 1;
	while (count <= info->philo_nbr)
	{
		pthread_create(&current->thread, NULL, philo_routine, current);
		current = current->next;
		count++;
	}
	current = p;
	count = 1;
	pthread_create(&guard, NULL, monitor, (void *)current);
	while (count <= info->philo_nbr)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		count++;
	}
	pthread_join(guard, NULL);
}
