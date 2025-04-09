/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:54:12 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:01:10 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
s: The string to be split.
c: The delimiter character.

RETURN VALUE
The array of new strings resulting from the split.
NULL if the allocation fails.

EXTERNAL FUNCTS. malloc, free

DESCRIPTION
Allocates (with malloc) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer. */
static int	countwords(char const *s, char c)
{
	size_t	i;
	size_t	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			wordcount++;
		i++;
	}
	return (wordcount);
}

static int	splitwords(char **result, char const *s, char c, size_t count)
{
	size_t		start;
	size_t		end;

	start = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			result[count] = malloc(sizeof(char) * (end - start + 2));
			if (!result[count])
			{
				while (count--)
					free(result[count]);
				return (0);
			}
			ft_strlcpy(result[count], (s + start), end - start + 2);
			count++;
		}
		end++;
	}
	result[count] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!result)
		return (NULL);
	if (!splitwords(result, s, c, 0))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
