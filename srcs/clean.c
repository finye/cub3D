#include "../incl/cub3D.h"

void	free_map(t_cub *cub)
{
	int	i;

	if (!cub->map)
		return ;
	i = 0;
	while (cub->map[i])
	{
		free(cub->map[i]);
		cub->map[i] = NULL;
		i++;
	}
	free(cub->map);
	cub->map = NULL;
}
