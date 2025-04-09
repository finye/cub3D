/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:38:44 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 13:05:54 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* DESCRIPTION
calloc() function allocates memory.

calloc() contiguously allocates enough space for count objects that are size
bytes of memory each and returns a pointer to the allocated memory. 
The allocated memory is filled with bytes of value zero.

The free() function deallocates the memory allocation pointed to by ptr. 
If ptr is a NULL pointer, no operation is performed.

RETURN VALUES
If successful, calloc() returns a pointer to allocated memory.  If there is 
an error, they return a NULL pointer and set errno to ENOMEM.

The free() function does not return a value. */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && (UINT_MAX / count) < size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
