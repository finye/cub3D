#include "../incl/cub3D.h"

void	map_not_last(t_cub *cub, char **words)
{
	err(MAP_NOT_LAST);
	free_exit(cub, words);
}

void	err(char *msg)
{
	printf(RED "Error\n" END);
	if (mlx_errno)
		printf("%s\n", mlx_strerror(mlx_errno));
	else if (msg)
		printf("%s\n", msg);
}
