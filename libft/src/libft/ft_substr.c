/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:30 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:28 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring.
---
DESCRIPTION
Allocates (with malloc) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (start > ft_strlen(s))
		return ((char *)ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub || !s)
		return (NULL);
	ft_strlcpy(sub, s + start, (len + 1));
	return (sub);
}
