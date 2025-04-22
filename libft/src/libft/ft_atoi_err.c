/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:55 by eelaine           #+#    #+#             */
/*   Updated: 2025/04/22 15:46:03 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	atoi_prepare(const char **str, int *sign)
{
	*sign = 1;
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}

static int	digits(const char **str, int sign, int *error, int *has_digits)
{
	long int	number;
	long int	check;

	number = 0;
	*has_digits = 0;
	while (**str >= 48 && **str <= 57)
	{
		*has_digits = 1;
		check = number;
		number = number * 10 + (**str - 48);
		if (number / 10 != check && sign > 0)
		{
			if (error)
				*error = 1;
			return (-1);
		}
		if (number / 10 != check && sign < 0)
		{
			if (error)
				*error = 1;
			return (0);
		}
		(*str)++;
	}
	return (sign * number);
}

int	ft_atoi_err(const char *str, int *error)
{
	int	sign;
	int	has_digits;
	int	result;

	if (error)
		*error = 0;
	atoi_prepare(&str, &sign);
	result = digits(&str, sign, error, &has_digits);
	if (*str != '\0' && error)
		*error = 2;
	if (!has_digits)
	{
		if (error)
			*error = 3;
		return (0);
	}
	return (result);
}
