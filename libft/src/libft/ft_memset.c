/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:49:12 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:57:21 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The memset() function writes len bytes of value c
(converted to an unsigned char) to the string b.

RETURN VALUES
The memset() function returns its first argument. */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*new;

	new = (unsigned char *)b;
	while (len-- > 0)
		*new++ = (unsigned char)c;
	return (b);
}
