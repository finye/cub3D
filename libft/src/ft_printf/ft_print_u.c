/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:53:31 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/13 11:29:13 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/ft_printf.h"

void	ft_uint(unsigned int n, int *err)
{
	if (n > 9)
		ft_print_u(n / 10, err);
	ft_print_char((n % 10) + '0', err);
}

int	ft_print_u(unsigned int n, int *err)
{
	int	i;

	i = 1;
	ft_uint(n, err);
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	if (*err == 1)
		return (-1);
	return (i);
}
