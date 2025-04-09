/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:04:28 by eelaine           #+#    #+#             */
/*   Updated: 2025/02/20 16:14:23 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/*DESCRIPTION
The realloc() function changes the size of the memory  block
pointed  to  by ptr to size bytes.  The contents will be un‐
changed in the range from the start of the region up to  the
minimum of the old and new sizes.  If the new size is larger
than the old size, the added memory will not be initialized.
If ptr is NULL, then the call is equivalent to malloc(size),
for all values of size; if size is equal to zero, and ptr is
not  NULL, then the call is equivalent to free(ptr).  Unless
ptr is NULL, it must have been returned by an  earlier  call
to malloc(), calloc(), or realloc().  If the area pointed to
was moved, a free(ptr) is done.

RETURN VALUE
The realloc() function returns a pointer to the newly  allo‐
cated  memory,  which  is  suitably aligned for any built-in
type, or NULL if the request failed.  The  returned  pointer
may  be  the  same  as  ptr  if the allocation was not moved
(e.g., there was room to expand the allocation in-place), or
different  from ptr if the allocation was moved to a new ad‐
dress.  If size was equal to 0, either  NULL  or  a  pointer
suitable  to  be passed to free() is returned.  If realloc()
fails, the original block is left untouched; it is not freed
or moved.*/
void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
