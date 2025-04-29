#include "../incl/cub3D.h"

static void	init_map(t_cub *cub)
{
	cub->map.height = 0;
	cub->map.width = 0;
}

static void	init_rgb(t_cub *cub)
{	
	cub->floor.r = -1;
	cub->floor.g = -1;
	cub->floor.b = -1;
	cub->ceiling.r = -1;
	cub->ceiling.g = -1;
	cub->ceiling.b = -1;
}

void	init(t_cub *cub, int fd, char *path)
{
	cub->fd = fd;
	cub->data = NULL;
	cub->line = 0;
	cub->col = 0;
	cub->line_count = 0;
	cub->path = path;
	cub->id_count = 0;
	cub->all_ids = false;
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	init_rgb(cub);
	init_map(cub);
}
