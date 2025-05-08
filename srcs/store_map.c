#include "../incl/cub3D.h"

static int	allocate_line(int i, t_cub *cub)
{
	cub->map.arr[i] = malloc(sizeof(char) * (cub->map.width + 1));
	if (!cub->map.arr[i])
	{
		while (--i >= 0)
		{
			free(cub->map.arr[i]);
			cub->map.arr[i] = NULL;
		}
		free(cub->map.arr);
		cub->map.arr = NULL;
		return (FAIL);
	}
	return (SUCCESS);
}

static int	store_map_lines(int current_line, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map.height)
	{
		if (allocate_line(i, cub) == FAIL)
			return (FAIL);
		j = 0;
		while (cub->data[current_line + i][j] && j < cub->map.width)
		{
			if (cub->data[current_line + i][j] == ' ')
				cub->map.arr[i][j] = ' ';
			else
				cub->map.arr[i][j] = cub->data[current_line + i][j];
			j++;
		}
		while (j < cub->map.width)
			cub->map.arr[i][j++] = ' ';
		cub->map.arr[i][j] = '\0';
	}
	cub->map.arr[cub->map.height] = NULL;
	return (SUCCESS);
}

static void	get_map_dimensions(int i, t_cub *cub)
{
	int	line_len;

	cub->map.height = 0;
	cub->map.width = 0;
	while (cub->data[i])
	{
		line_len = ft_strlen(cub->data[i]);
		if (line_len > cub->map.width)
			cub->map.width = line_len;
		cub->map.height++;
		i++;
	}
}

int	store_map(int current_line, t_cub *cub)
{
	get_map_dimensions(current_line, cub);
	if (cub->map.width > MAX_WIDTH || cub->map.height > MAX_HEIGHT)
		return (err(MAP_TOO_BIG), FAIL);
	cub->map.arr = NULL;
	cub->map.arr = malloc(sizeof(char *) * (cub->map.height + 1));
	if (!cub->map.arr)
		return (err(MALLOC_MAP), FAIL);
	if (store_map_lines(current_line, cub) == FAIL)
		return (err(MALLOC_MAP_LINE), FAIL);
	return (SUCCESS);
}
