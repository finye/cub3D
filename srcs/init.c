#include "../incl/cub3D.h"

void	init(t_cub *cub, int fd, char *path)
{
	cub->fd = fd;
	cub->map = NULL;
	cub->row = 0;
	cub->col = 0;
	cub->row_count = 0;
	cub->path = path;
}
