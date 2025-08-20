/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nb_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:02:07 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 17:01:00 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	mtx_get_last_meal(t_philo *p)
{
	long	time_last_meal;

	pthread_mutex_lock(&p->mtx_meal);
	time_last_meal = p->time_last_meal;
	pthread_mutex_unlock(&p->mtx_meal);
	return (time_last_meal);
}

bool	check_meal_count(t_philo *p)
{
	if (!p->info->nbr_time_eat)
		return (false);
	pthread_mutex_lock(&p->mtx_meal);
	if (p->meal_count < p->info->nbr_time_eat)
	{
		pthread_mutex_unlock(&p->mtx_meal);
		return (false);
	}
	pthread_mutex_unlock(&p->mtx_meal);
	return (true);
}

bool	is_mealcount_max(t_philo *p)
{
	if (!p->info->nbr_time_eat)
		return (false);
	if (p->is_maxmeal_reached)
		return (true);
	pthread_mutex_lock(&p->mtx_meal);
	p->is_maxmeal_reached = p->meal_count >= p->info->nbr_time_eat;
	pthread_mutex_unlock(&p->mtx_meal);
	return (p->is_maxmeal_reached);
}

bool	check_all_philosophers_meals(t_philo *p)
{
	int		index;
	int		flag;
	t_philo	*current;

	current = p->next;
	index = 0;
	flag = 0;
	while (index < p->info->philo_nbr)
	{
		if (is_mealcount_max(current))
			flag++;
		current = current->next;
		index++;
		if (index != flag)
			return (false);
	}
	pthread_mutex_lock(&p->info->mtx_info);
	p->info->end_simulation = true;
	pthread_mutex_unlock(&p->info->mtx_info);
	return (true);
}

bool	die_engine(t_philo *p, long total_time)
{
	long	tmp_time;

	if (total_time >= p->info->time_to_die && p->info->time_to_die)
	{
		pthread_mutex_lock(&p->info->mtx_info);
		tmp_time = get_time_simulation(p->info->time_to_start);
		p->info->end_simulation = true;
		printf("%s%ld %d %s%s\n", RED,
			tmp_time, p->id, "died", NC);
		pthread_mutex_unlock(&p->info->mtx_info);
		return (true);
	}
	return (false);
}
