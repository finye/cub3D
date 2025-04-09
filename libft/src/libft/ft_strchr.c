/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:19:50 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:01:15 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The strchr() function locates the first occurrence of c 
(converted to a char) in the string pointed to by s. The terminating 
null character is considered to be part of the string; therefore 
if c is `\0', the functions locate the terminating `\0'.

RETURN VALUES
The functions strchr() and strrchr() return a pointer to the located 
character, or NULL if the character does not appear in the string. */
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
