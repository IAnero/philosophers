/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <herrakot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:06:16 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/10 15:38:06 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	info;

	if (ac > 6 || ac <= 4 || ft_atol(av[1]) == 0)
	{
		ft_error_arg(av);
		return (1);
	}
	struct_init(&info);
	if (check_validity_arg(av) == 0)
	{
		ft_errorvalidity_arg(av);
		return (1);
	}
	init_data_routine(av, &info);
	philo = init_table(&info);
	ft_mtx_destroy(philo);
	return (0);
}
