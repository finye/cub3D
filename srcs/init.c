#include "../incl/cub3D.h"

void	init(t_cub *cub, int fd, char *path)
{
	cub->fd = fd;
	cub->data = NULL;
	cub->line = 0;
	cub->col = 0;
	cub->line_count = 0;
	cub->path = path;
	cub->id_count = 0;
	cub->floor.r = -1;
	cub->floor.g = -1;
	cub->floor.b = -1;
	cub->ceiling.r = -1;
	cub->ceiling.g = -1;
	cub->ceiling.b = -1;
}
