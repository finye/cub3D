#include "../incl/cub3D.h"

static int	is_player_found(t_cub *cub)
{
	if (!cub->map.pos_found)
		return (err(NO_PLAYER), FAIL);
	return (SUCCESS);
}

static void	get_surrounding_chars(int i, int j, t_cub *cub)
{
	if (j > 0)
		cub->map.left = cub->map.arr[i][j - 1];
	else
		cub->map.left = ' ';
	if (j + 1)
	{
		cub->map.right = cub->map.arr[i][j + 1];
		if (cub->map.arr[i][j + 1] == '\n' || cub->map.arr[i][j + 1] == '\0')
			cub->map.right = ' ';
	}
	else
		cub->map.right = ' ';
	if (i > 0)
		cub->map.above = cub->map.arr[i - 1][j];
	else
		cub->map.above = ' ';
	if (i >= 0 && i < cub->map.height - 1)
	{
		cub->map.below = cub->map.arr[i + 1][j];
		if (cub->map.below == '\n' || cub->map.below == '\0')
			cub->map.below = ' ';
	}
	else
		cub->map.below = ' ';
}

static int	check_forbidden_chars(t_cub *cub, int i, int j, char c)
{
	if (!ft_strchr("10NSWE\n \0", c))
		return (err(FORBIDDEN_CHARS), FAIL);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (cub->map.pos_found)
			return (err(MULTI_START), FAIL);
		if (cub->map.above == ' ' || cub->map.below == ' '
			|| cub->map.left == ' ' || cub->map.right == ' ')
			return (err(OUT_OF_BOUNDS), FAIL);
		cub->map.pos_found = true;
		cub->p.player_coord_x = j;
		cub->p.player_coord_y = i;
		cub->p.player_heading = c;
	}
	if (c == '0' && (cub->map.above == ' ' || cub->map.below == ' '
			|| cub->map.left == ' ' || cub->map.right == ' '))
		return (err(WALL_ERROR), FAIL);
	return (SUCCESS);
}

int	validate_map(t_cub *cub)
{
	int	i;
	int	j;

	if (!cub->map.arr)
		return (FAIL);
	i = 0;
	while (cub->map.arr[i])
	{
		j = 0;
		while (cub->map.arr[i][j])
		{
			get_surrounding_chars(i, j, cub);
			if (check_forbidden_chars(cub, i, j, cub->map.arr[i][j]) == FAIL)
				return (free_exit(cub, 0), FAIL);
			j++;
		}
		i++;
	}
	if (is_player_found(cub) == FAIL)
		return (free_exit(cub, 0), FAIL);
	return (SUCCESS);
}
