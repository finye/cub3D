#include "../incl/cub3D.h"

static mlx_texture_t	*load_texture(t_cub *cub, char *path)
{
	mlx_texture_t	*texture;
	char			*trimmed_path;

	if (!path)
		return (NULL);
	trimmed_path = ft_strtrim(path, "\n");
	if (!trimmed_path)
	{
		free_exit(cub, NULL);
		return (err(TEX_TRIM_FAIL), NULL);
	}
	texture = mlx_load_png(trimmed_path);
	free(trimmed_path);
	if (!texture)
	{
		err(TEX_LOAD_FAIL);
		free_exit(cub, NULL);
		return (NULL);
	}
	return (texture);
}

void	cleanup_textures(t_cub *cub)
{
	if (cub->north_tex)
		mlx_delete_texture(cub->north_tex);
	if (cub->south_tex)
		mlx_delete_texture(cub->south_tex);
	if (cub->west_tex)
		mlx_delete_texture(cub->west_tex);
	if (cub->east_tex)
		mlx_delete_texture(cub->east_tex);
	cub->north_tex = NULL;
	cub->south_tex = NULL;
	cub->west_tex = NULL;
	cub->east_tex = NULL;
}

int	load_all_textures(t_cub *cub)
{
	cub->north_tex = load_texture(cub, cub->north);
	cub->south_tex = load_texture(cub, cub->south);
	cub->west_tex = load_texture(cub, cub->west);
	cub->east_tex = load_texture(cub, cub->east);
	if (!cub->north_tex || !cub->south_tex || !cub->west_tex || !cub->east_tex)
	{
		printf("REACHED CLEANUP TEXTURES\n");
		cleanup_textures(cub);
		return (FAIL);
	}
	return (SUCCESS);
}

int	validate_texture(char *content)
{
	int	len;

	if (content)
	{
		len = ft_strlen(content);
		if (len < 6 || !ft_strnstr(&content[len - 5], ".png\n", 5)
			|| ft_strnstr(&content[len - 6], "/.png\n", 6))
			return (err(TEX_EXT), FAIL);
	}
	return (SUCCESS);
}
