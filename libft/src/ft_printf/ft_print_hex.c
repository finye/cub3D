/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:16:54 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/13 11:29:03 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/ft_printf.h"

int	ft_hex_len(unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (i + 1);
	while (n)
	{
		i++;
		n /= 16;
	}
	return (i);
}

void	ft_put_hex(unsigned int n, const char format, int *err)
{
	if (n >= 16)
	{
		ft_put_hex(n / 16, format, err);
		ft_put_hex(n % 16, format, err);
	}
	else
	{
		if (n <= 9)
			ft_print_char(n + '0', err);
		else
		{
			if (format == 'x')
				ft_print_char(n - 10 + 'a', err);
			if (format == 'X')
				ft_print_char(n - 10 + 'A', err);
		}
	}
}

int	ft_print_hex(unsigned int num, const char format, int *err)
{
	if (num == 0)
		ft_print_char('0', err);
	else
		ft_put_hex(num, format, err);
	if (*err == 1)
		return (-1);
	return (ft_hex_len(num));
}
