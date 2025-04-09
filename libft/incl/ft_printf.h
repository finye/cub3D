/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:07 by eelaine           #+#    #+#             */
/*   Updated: 2024/05/13 11:45:07 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

int		ft_printf(const char *str, ...);
int		ft_print_char(int c, int *err);
int		ft_print_ptr(void *ptr, int *err);
int		ft_print_str(char *s, int *err);
int		ft_print_nbr(int n, int *err);
int		ft_print_hex(unsigned int num, const char format, int *err);
int		ft_print_u(unsigned int n, int *err);

#endif
