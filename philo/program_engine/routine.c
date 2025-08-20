/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:16:29 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 16:40:44 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	eat(t_philo *p)
{
	if (!ft_print(p, "has taken a fork", NC))
		return (false);
	if (!ft_print(p, "has taken a fork", NC))
		return (false);
	if (!ft_print(p, "is eating", GREEN))
		return (false);
	pthread_mutex_lock(&p->mtx_meal);
	p->time_last_meal = get_time() - p->info->time_to_start;
	p->time_last_meal_by_monitor = get_time() - p->info->time_to_start;
	p->meal_count++;
	if (p->meal_count >= p->info->nbr_time_eat && p->info->nbr_time_eat)
	{
		pthread_mutex_unlock(&p->mtx_meal);
		return (false);
	}
	pthread_mutex_unlock(&p->mtx_meal);
	my_usleep(p, p->info->time_to_eat);
	p->state = SLEEP;
	return (true);
}

bool	slep(t_philo *p)
{
	if (!ft_print(p, "is sleeping", YELLOW))
		return (false);
	my_usleep(p, p->info->time_to_sleep);
	p->state = THINKING;
	return (true);
}

bool	think(t_philo *p)
{
	if (!ft_print(p, "is thinking", BYELLOW))
		return (false);
	if (p->info->philo_nbr % 2 != 0)
		usleep(p->info->time_to_eat * 1000);
	usleep(10);
	p->state = EATING;
	return (true);
}

bool	is_dead(t_philo *p)
{
	t_philo	*current;
	long	time;
	long	total_time;
	long	time_last_meal;

	time = get_time();
	current = p;
	if (p->info->philo_nbr % 2)
		time_last_meal = time_assignation(p);
	else
		time_last_meal = mtx_get_last_meal(current);
	total_time = time - current->info->time_to_start - time_last_meal;
	if (die_engine(p, total_time))
		return (true);
	return (is_stop(p));
}

bool	is_stop(t_philo *p)
{
	if (!check_meal_count(p))
		return (false);
	return (check_all_philosophers_meals(p));
}
