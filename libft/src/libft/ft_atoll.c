/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:18:55 by eelaine           #+#    #+#             */
/*   Updated: 2025/01/15 15:08:07 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	number;
	long long	check;

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
