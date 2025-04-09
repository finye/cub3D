/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:33:07 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:01:48 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The strlcpy() function copies strings.

strlcpy() takes the full size of the destination buffer and guarantees 
NUL-termination if there is room. Note that room for the NUL should be 
included in dstsize.

strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
NUL-terminating the result if dstsize is not 0.

If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
strlcpy() returns the total length of the string it tries to create. 
For strlcpy() that means the length of src.

If the return value is >= dstsize, the output string has been truncated. 
It is the caller's responsibility to handle this. */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
	return (ft_strlen(src));
}
