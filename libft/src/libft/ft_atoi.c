/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:27:33 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:55:20 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The atoi() function converts the initial portion of the string pointed to by 
str to int representation. 

It is equivalent to: (int)strtol(str, (char **)NULL, 10);*/
int	ft_atoi(const char *str)
{
	int			sign;
	long int	number;
	long int	check;

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
	while (*str >= 48 && *str <= 57)
	{
		check = number;
		number = number * 10 + (*str - 48);
		if (number / 10 != check && sign > 0)
			return (-1);
		if (number / 10 != check && sign < 0)
			return (0);
		str++;
	}
	return (sign * number);
}
