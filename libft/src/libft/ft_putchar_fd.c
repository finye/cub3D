/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:25:45 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:57:26 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/* PARAMETERS
c: The character to output.
fd: The file descriptor on which to write.

RETURN VALUE None

EXTERNAL FUNCTS. write

DESCRIPTION
Outputs the character ’c’ to the given file
descriptor. */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
