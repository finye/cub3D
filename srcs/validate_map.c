#include "../incl/cub3D.h"

int	validate_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	if (!cub->map.arr)
		return (FAIL);
	while (cub->map.arr[++i])
	{
		j = -1;
		while (cub->map.arr[i][++j] != '\0')
		{
			if (!ft_strchr("10NSWE'\n' '", cub->map.arr[i][j]))
			{
				printf("current char: %c", cub->map.arr[i][j]);
				err(FORBIDDEN_CHARS);
				free_cub(cub);
				return (FAIL);
			}
		}
	}
	/* if (ft_find(data->map, 'C') == 0)
		ft_map_err(6, data);
	if (ft_find(data->map, 'E') != 1)
		ft_map_err(7, data);
	if (ft_find(data->map, 'P') != 1)
		ft_map_err(8, data); */
	return (SUCCESS);
}
