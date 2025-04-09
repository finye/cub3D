/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:59:22 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/20 12:55:05 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"
/*DESCRIPTION
The  abs() function computes the absolute value of the inte‐
ger argument.

RETURN VALUE
Returns the absolute value of the integer argument,  of  the
appropriate integer type for the function.*/
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}
