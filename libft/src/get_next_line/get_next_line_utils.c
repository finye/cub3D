/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:38:13 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/28 15:05:39 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/get_next_line.h"

char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen_gnl(s);
	if (start > slen)
		return (NULL);
	if (len > slen + start)
		len = slen + start;
	sub = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub)
	{
		free(sub);
		return (NULL);
	}
	ft_strlcpy_gnl(sub, s + start, (len + 1));
	return (sub);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	size_t		i;
	size_t		i2;
	size_t		s1_len;
	size_t		s2_len;
	char		*s3;

	i = 0;
	i2 = 0;
	if (!s1)
		s1 = "";
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	s3 = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!s3)
		return (NULL);
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	while (i2 < s2_len)
		s3[i++] = s2[i2++];
	s3[i] = '\0';
	return (s3);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen_gnl(src));
}
