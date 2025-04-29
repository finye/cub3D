/* #include "../incl/cub3D.h"

static int	load_texture(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	free(texture);
	if (!*texture)
		return (err(0), FAIL);
	return (SUCCESS);
}

static int	id_texture(char *id, mlx_texture_t	***texture, t_cub *cub)
{
	if (!ft_strncmp("NO\0", id, 3) || !ft_strncmp("NO\n", id, 3))
		*texture = &(cub->north);
	if (!ft_strncmp("SO\0", id, 3) || !ft_strncmp("SO\n", id, 3))
		*texture = &(cub->south);
	if (!ft_strncmp("WE\0", id, 3) || !ft_strncmp("WE\n", id, 3))
		*texture = &(cub->west);
	if (!ft_strncmp("EA\0", id, 3) || !ft_strncmp("EA\n", id, 3))
		*texture = &(cub->north);
	else
		return (err(NOT_ID), FAIL);
	return (SUCCESS);
}

static int	get_texture(char *id, char *path, t_cub *cub)
{
	mlx_texture_t	**texture;
	char			*trimmed_path;

	texture = NULL;
	if (id_texture(id, &texture, cub) == FAIL)
		return (FAIL);
	if (*texture)
		return (err(MULTI_WALL_ID), FAIL);
	if (!path || *path == '\n')
		return (err(NO_TEXTURE_PATH), FAIL);
	trimmed_path = ft_strtrim(path, "\n");
	if (!trimmed_path)
		return (FAIL);
	if (load_texture(trimmed_path, texture) == FAIL)
		return (FAIL);
	cub->id_count++;
}

int	parse_line(char **split_line, t_cub *cub)
{
	if (split_line[0][0] == 'F' || split_line[0][0] == 'C')
	{
		if (set_floor_ceiling(split_line[0], split_line[1], cub) == FAIL)
			return (FAIL);
	}
	if (get_texture(split_line[0], split_line[1], cub) == FAIL)
		return (FAIL);
	if (split_line[2] && split_line[2][0] != '\n')
		return (err(EXTRA_VALUE), FAIL);
	return (SUCCESS);
}
 */