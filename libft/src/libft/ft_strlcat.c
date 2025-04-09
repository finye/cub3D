/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:30:47 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:01:43 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
The strlcat() function concatenates strings.

strlcat() takes the full size of the destination buffer and guarantees 
NUL-termination if there is room. Note that room for the NUL should be 
included in dstsize.

strlcat() appends string src to the end of dst.  It will append at most 
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, 
unless dstsize is 0 or the original dst string was longer than dstsize 
(in practice this should not happen as it means that either dstsize is 
incorrect or that dst is not a proper string).

If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
strlcat() function returns the total length of the string it tried to create 
meaning the initial length of dst plus the length of src.

If the return value is >= dstsize, the output string has been truncated. 
It is the caller's responsibility to handle this. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	src_len;
	unsigned int	dst_len;
	unsigned int	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (dstsize + src_len);
	while (src[i] && (dst_len + i < dstsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
