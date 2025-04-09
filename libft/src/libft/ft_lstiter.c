/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:45 by eelaine           #+#    #+#             */
/*   Updated: 2024/09/02 09:54:46 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.

RETURN VALUE None

EXTERNAL FUNCTS. None

DESCRIPTION
Iterates the list ’lst’ and applies the function
’f’ on the content of each node. */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
