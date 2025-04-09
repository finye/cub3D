/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:00:56 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/13 11:29:08 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/ft_printf.h"

size_t	ft_ptr_len(size_t n)
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

void	ft_put_ptr(uintptr_t n, int *err)
{
	if (n >= 16)
	{
		ft_put_ptr(n / 16, err);
		ft_put_ptr(n % 16, err);
	}
	else
	{
		if (n < 10)
			ft_print_char(n + '0', err);
		else
			ft_print_char(n - 10 + 'a', err);
	}
}

int	ft_print_ptr(void *ptr, int *err)
{
	size_t		len;
	uintptr_t	p;

	len = 0;
	p = (uintptr_t)ptr;
	len += ft_print_str("0x", err);
	if (!p)
		len += ft_print_char('0', err);
	else
	{
		ft_put_ptr(p, err);
		len += ft_ptr_len(p);
	}
	if (*err == 1)
		return (-1);
	return (len);
}
