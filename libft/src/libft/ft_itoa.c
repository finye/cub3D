/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:12:01 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:56:11 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
n: the integer to convert.

RETURN VALUE
The string representing the integer.
NULL if the allocation fails.

EXTERNAL FUNCTS. malloc

DESCRIPTION
Allocates (with malloc) and returns a string
representing the integer received as an argument.
Negative numbers must be handled. */
static size_t	numlen(long int n)
{
	size_t		i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	size_t		len;
	char		*str;

	nbr = (long int)n;
	len = numlen(n);
	if (n < 0)
	{
		nbr *= -1;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len--)
	{
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
