#include "../incl/cub3D.h"

static int	atoi_color(char *color)
{
	int	number;
	int	error;

	error = 0;
	if (!color)
		return (ERROR);
	if (!ft_isdigit(*color))
		return (FAIL);
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
	int	color;

	color = atoi_color(rgb[0]);
	if (color == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->r = color;
	color = atoi_color(rgb[1]);
	if (color == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->g = color;
	color = atoi_color(rgb[2]);
	if (color == ERROR)
		return (err(WRONG_RGB_VALUE), FAIL);
	color->b = color;
	return (SUCCESS);
}

static int	get_color(char *color_info, int location, t_cub *cub)
{
	char	**rgb;
	t_rgb	*color;

	if (cub->floor.r != -1)
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
	cub->id_count++;
	return (free_split(rgb), FAIL);
}

int	set_floor_ceiling(char *id, char *color_info, t_cub *cub)
{
	if (!ft_strcmp("F\0", id))
	{
		if (cub->floor.r != -1)

		return (get_color(color_info, F, cub));
	}
	else if (!ft_strcmp("C\0", id))
	{
		if (cub->ceiling.r != -1)
			return (err(MULTI_COLOR_ID), FAIL);
		return (get_color(color_info, C, cub));
	}
	return (err(NO_ID), FAIL);
}
