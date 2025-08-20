/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:29:29 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 16:11:36 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philo	*init_table(t_data *info)
{
	t_philo	*p;
	t_philo	*new_p;
	t_philo	*last;
	t_philo	*current;
	int		count;

	p = NULL;
	count = 1;
	while (count <= info->philo_nbr)
	{
		new_p = init_philos(count, info);
		add_back(&p, new_p);
		count++;
	}
	last = p;
	while (last->next)
		last = last->next;
	last->next = p;
	current = p;
	count = 1;
	info->time_to_start = get_time();
	create(info, current);
	return (p);
}

long	get_time_simulation(long time)
{
	return (get_time() - time);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	bool	can_continue;

	can_continue = true;
	philo = (t_philo *)arg;
	if (philo->info->philo_nbr == 1)
		return (is_alone(philo));
	if (philo->info->nbr_eat_zero == 0)
		return (NULL);
	while (can_continue)
	{
		if (philo->state == EATING)
		{
			fork_lock(philo);
			can_continue = eat(philo);
			fork_unlock(philo);
		}
		if (can_continue && philo->state == SLEEP)
			can_continue = slep(philo);
		if (can_continue && philo->state == THINKING)
			can_continue = think(philo);
		usleep(100);
	}
	return (NULL);
}

void	*is_alone(t_philo *p)
{
	t_philo	*current;

	current = p;
	ft_print(p, "has taken a fork", NC);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*p;
	t_philo	*current;
	int		index;

	p = (t_philo *)arg;
	current = p;
	index = 0;
	while (p->info->nbr_eat_zero != 0)
	{
		index++;
		if (is_dead(current))
			return (NULL);
		current = current->next;
		if (index % p->info->philo_nbr == 0)
			usleep(100);
	}
	return (NULL);
}
