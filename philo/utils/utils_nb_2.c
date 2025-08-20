/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nb_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:03:29 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 16:40:56 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	fork_lock(t_philo *philo)
{
	if (philo->state == EATING && (philo->id == philo->info->philo_nbr))
	{
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
	}
	philo->has_fork = true;
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	ft_print(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->info->mtx_info);
	if (!philo->info->end_simulation)
	{
		printf("%s%ld %d %s%s\n", color,
			get_time_simulation(philo->info->time_to_start),
			philo->id, str, NC);
		pthread_mutex_unlock(&philo->info->mtx_info);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->mtx_info);
	return (false);
}

void	my_usleep(t_philo *p, int time)
{
	long	start;
	long	end;

	(void)p;
	start = get_time();
	end = start + time;
	while (get_time() < end)
		usleep(100);
}

long	time_assignation(t_philo *p)
{
	t_philo	*current;
	long	curtime;
	long	todie;
	long	rest;
	long	time_last_meal;

	current = p;
	curtime = get_time() - p->info->time_to_start;
	pthread_mutex_lock(&p->mtx_meal);
	todie = p->time_last_meal_by_monitor + p->info->time_to_die;
	pthread_mutex_unlock(&p->mtx_meal);
	rest = todie - curtime;
	if (rest < 10)
	{
		pthread_mutex_lock(&p->mtx_meal);
		time_last_meal = p->time_last_meal_by_monitor;
		p->time_last_meal_by_monitor = 0;
		pthread_mutex_unlock(&p->mtx_meal);
	}
	else
		time_last_meal = mtx_get_last_meal(current);
	return (time_last_meal);
}
