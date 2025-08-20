/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nb_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:56:04 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/09 17:37:31 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_is_in(char c, char *s)
{
	int	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x] != '\0')
	{
		if (s[x] == c)
			return (1);
		x++;
	}
	return (0);
}

int	ft_is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_is_in(s[i], "+0123456789"))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	ft_mtx_destroy(t_philo *p)
{
	t_philo	*current;
	int		x;
	t_philo	*tmp;
	int		p_nbr;

	p_nbr = 0;
	p_nbr = p->info->philo_nbr;
	current = p;
	x = 1;
	pthread_mutex_destroy(&current->info->mtx_info);
	pthread_mutex_destroy(&current->mtx_meal);
	while (x <= p_nbr)
	{
		tmp = current;
		pthread_mutex_destroy(&current->fork);
		current = current->next;
		free (tmp);
		x++;
	}
}

void	fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->has_fork = false;
}
