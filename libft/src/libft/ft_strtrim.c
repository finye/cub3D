/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:47:42 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:22 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
s1: The string to be trimmed.
set: The reference set of characters to trim.

DESCRIPTION
Allocates (with malloc) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string. */
static int	checktrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*s2;

	i = 0;
	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && checktrim(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && checktrim(s1[end - 1], set))
		end--;
	s2 = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!s2)
		return (NULL);
	while (start < end)
		s2[i++] = s1[start++];
	s2[i] = 0;
	return (s2);
}
