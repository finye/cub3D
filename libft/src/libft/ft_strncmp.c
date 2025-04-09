/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:59 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:05 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
strncmp() function lexicographically compares the null-terminated strings s1 
and s2.

The strncmp() function compares not more than n characters.  Because strncmp() 
is designed for comparing strings rather than binary data, characters that 
appear after a `\0' character are not compared.

RETURN VALUES
strncmp() function returns an integer greater than, equal to, or less than 0, 
according as the string s1 is greater than, equal to, or less than the string 
s2.  The comparison is done using unsigned characters, so that `\200' is 
greater than `\0'. */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (*s1 != '\0' && *s2 != '\0' && i < n - 1)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
		i++;
	}
	if (i != n)
	{
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (0);
}
