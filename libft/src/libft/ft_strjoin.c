/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:17:02 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:01:37 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS 
s1: The prefix string.
s2: The suffix string.

DESCRIPTION
Allocates (with malloc) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		i2;
	char		*s3;

	i = 0;
	i2 = 0;
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s3[i] = s1[i];
		i++;
	}
	while (i2 < ft_strlen(s2))
	{
		s3[i] = s2[i2];
		i++;
		i2++;
	}
	s3[i] = '\0';
	return (s3);
}
