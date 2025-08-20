/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:43:28 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/07 11:28:07 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_error_arg(char *av[])
{
	(void)av;
	printf("%sToo much or not enough argument%s\n", RED, NC);
	return ;
}

void	ft_errorvalidity_arg(char *av[])
{
	(void)av;
	printf("%sThe argument should only be number%s\n", RED, NC);
	return ;
}
