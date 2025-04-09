/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:31:17 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:57:48 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
s: The string to output.
fd: The file descriptor on which to write.

RETURN VALUE None

EXTERNAL FUNCTS. write

DESCRIPTION
Outputs the string ’s’ to the given file
descriptor. */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
