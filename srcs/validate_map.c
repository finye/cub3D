#include "../incl/cub3D.h"

static void	get_surrounding_chars(int i, int j, t_cub *cub)
{
	if (j > 0)
		cub->map.left = cub->map.arr[i][j - 1];
	else
		cub->map.left = ' ';
	if (j < cub->map.width - 2)
		cub->map.right = cub->map.arr[i][j + 1];
	else
		cub->map.right = ' ';
	if (i > 0)
		cub->map.above = cub->map.arr[i - 1][j];
	else
		cub->map.above = ' ';
	if (i >= 0 && i < cub->map.height - 1)
		cub->map.below = cub->map.arr[i + 1][j];
	else
		cub->map.below = ' ';
}

static int	check_forbidden_chars(t_cub *cub, char c)
{
	if (!ft_strchr("10NSWE'\n' '", c))
		return (err(FORBIDDEN_CHARS), FAIL);
	if (ft_strchr("NSWE", c) && cub->map.pos_found)
		return (err(MULTI_START), FAIL);
	if (ft_strchr("NSWE", c))
		cub->map.pos_found = true;
	if (ft_strchr("NSWE", c) && (cub->map.above == ' ' || cub->map.below == ' '
		|| cub->map.left == ' ' || cub->map.right == ' '))
		return (err(OUT_OF_BOUNDS), FAIL);
	return (SUCCESS);
}

/* static int	check_player_pos(t_cub *cub, char c)
{

} */

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
			get_surrounding_chars(i, j, cub);
			if (check_forbidden_chars(cub, cub->map.arr[i][j]) == FAIL)
				return (free_exit(cub, 0), FAIL);
			/* if (check_player_pos(cub, cub->map.arr[i][j]) == FAIL)
				return (free_exit(cub, 0), FAIL); */
		}
	}
	return (SUCCESS);
}
