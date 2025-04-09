/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:53:23 by eelaine           #+#    #+#             */
/*   Updated: 2025/03/06 13:16:49 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/ft_printf.h"

int	ft_print_char(int c, int *err)
{
	c = (char)c;
	if (*err == 1)
		return (-1);
	if (write(1, &c, 1) == -1)
	{
		*err = 1;
		return (-1);
	}
	return (1);
}

int	ft_formats(va_list args, const char format, int *err)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_print_char(va_arg(args, int), err);
	else if (format == 's')
		i += ft_print_str(va_arg(args, char *), err);
	else if (format == 'd' || format == 'i')
		i += ft_print_nbr(va_arg(args, int), err);
	else if (format == 'p')
		i += ft_print_ptr(va_arg(args, void *), err);
	else if (format == 'u')
		i += ft_print_u(va_arg(args, unsigned int), err);
	else if (format == 'x' || format == 'X')
		i += ft_print_hex(va_arg(args, unsigned int), format, err);
	else if (format == '%')
		i += ft_print_char('%', err);
	else
		return (0);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		result;
	int		err;

	va_start(args, str);
	err = 0;
	i = 0;
	result = 0;
	while (str[i])
	{
		if (err == 1)
			return (-1);
		else if (str[i] == '%' && str[i + 1] != '\0')
			result += ft_formats(args, str[i++ + 1], &err);
		else if (str[i] != '%')
			result += ft_print_char(str[i], &err);
		i++;
	}
	va_end(args);
	return (result);
}
