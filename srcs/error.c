#include "../incl/cub3D.h"

void	err(char *msg)
{
	printf(RED "Error\n" END);
	if (mlx_errno)
		printf("%s\n", mlx_strerror(mlx_errno));
	else if (msg)
		printf("%s\n", msg);
}
