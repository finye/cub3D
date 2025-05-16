/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:48:09 by eelaine           #+#    #+#             */
/*   Updated: 2025/05/16 08:48:11 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static int	atoi_color(char *color)
{
	int	number;
	int	error;

	error = 0;
	if (!color)
		return (ERROR);
	if (color[ft_strlen(color) - 1] == '\n')
		color[ft_strlen(color) - 1] = '\0';
	number = ft_atoi_err(color, &error);
	if (error)
		return (ERROR);
	if (number >= 0 && number <= 255)
		return (number);
	return (ERROR);
}

static int	set_rgb(t_rgb *color, char **rgb)
{
	int	rgb_value;

	rgb_value = atoi_color(rgb[0]);
	if (rgb_value == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->r = rgb_value;
	rgb_value = atoi_color(rgb[1]);
	if (rgb_value == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->g = rgb_value;
	rgb_value = atoi_color(rgb[2]);
	if (rgb_value == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->b = rgb_value;
	return (SUCCESS);
}

int	get_color(char *color_info, int location, t_cub *cub)
{
	char	**rgb;
	t_rgb	*color;

	if ((location == F && cub->floor.r != -1)
		|| (location == C && cub->ceiling.r != -1))
		return (err(MULTI_COLOR_ID), FAIL);
	if (location == F)
		color = &(cub->floor);
	else
		color = &(cub->ceiling);
	rgb = ft_split(color_info, ',');
	if (!rgb)
		return (err(0), FAIL);
	if (set_rgb(color, rgb) == FAIL)
		return (free_split(rgb), FAIL);
	if (rgb[3])
	{
		free_split(rgb);
		return (err(EXTRA_RGB), FAIL);
	}
	return (free_split(rgb), SUCCESS);
}
