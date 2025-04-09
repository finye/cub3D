/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:45:55 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/13 11:36:11 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/ft_printf.h"

int	ft_print_str(char *s, int *err)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) != 6)
		{
			*err = 1;
			return (-1);
		}
		return (6);
	}
	while (s[i])
		ft_print_char(s[i++], err);
	if (*err == 1)
		return (-1);
	return (i);
}

int	ft_print_nbr(int n, int *err)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		i += ft_print_str("-2147483648", err);
	else
	{
		if (n < 0)
		{
			i += ft_print_char('-', err);
			n *= -1;
		}
		if (n > 9)
			i += ft_print_nbr((n / 10), err);
		i += ft_print_char((n % 10) + '0', err);
	}
	if (*err == 1)
		return (-1);
	return (i);
}
