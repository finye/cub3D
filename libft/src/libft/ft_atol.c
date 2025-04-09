/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:19 by eelaine           #+#    #+#             */
/*   Updated: 2025/01/29 14:32:50 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/*
DESCRIPTION
     The atol() function converts the initial portion of the string pointed to
     by str to long integer representation.
*/
long	ft_atol(const char *str)
{
	int		sign;
	long	number;
	long	check;

	sign = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		check = number;
		number = number * 10 + (*str - '0');
		if (number / 10 != check && sign > 0)
			return (-1);
		if (number / 10 != check && sign < 0)
			return (0);
		str++;
	}
	return (sign * number);
}
