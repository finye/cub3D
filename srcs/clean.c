#include "../incl/cub3D.h"

void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub->data)
		return ;
	i = 0;
	while (cub->data[i])
	{
		free(cub->data[i]);
		cub->data[i] = NULL;
		i++;
	}
	free(cub->data);
	cub->data = NULL;
}

void	free_exit(t_cub *cub, char **split)
{
	free_split(split);
	free_cub(cub);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
