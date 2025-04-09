/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:07:22 by eelaine           #+#    #+#             */
/*   Updated: 2025/01/29 14:32:28 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
       The strpbrk() function locates the first occurrence in the string s of 
	   any of the bytes in the string accept.

RETURN VALUE
       The strpbrk() function returns a pointer to the byte in s that matches 
	   one of the bytes in accept, or NULL if no such byte is found. */
char	*ft_strpbrk(const char *s, const char *accept)
{
	const char	*a;

	if (!s || !accept)
		return (NULL);
	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
				return ((char *)s);
			a++;
		}
		s++;
	}
	return (NULL);
}
