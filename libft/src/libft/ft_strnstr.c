/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:28:43 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:10 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The strnstr() function locates the first occurrence of the null-terminated 
string needle in the string haystack, where not more than len characters are 
searched.  Characters that appear after a `\0' character are not searched.

RETURN VALUES
If needle is an empty string, haystack is returned; if needle occurs nowhere 
in haystack, NULL is returned; otherwise a pointer to the first character of 
the first occurrence of needle is returned. */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	nlen = 0;
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	while (ft_strncmp(&haystack[i], needle, nlen) != 0)
	{
		if (!haystack[i] || i >= (len - nlen))
			return (NULL);
		i++;
	}
	if (nlen > len)
		return (NULL);
	return ((char *)(&haystack[i]));
}
