#include "../incl/cub3D.h"

int	store_identifiers(char *content, int type, t_cub *cub)
{
	if (type != NONE && !content)
		return (err(NO_CONTENT), FAIL);
	if (content && type != NONE)
	{
		cub->id_count++;
		if (cub->id_count == 6)
			cub->all_ids = true;
		if (type == NO)
			cub->north = ft_strdup(content);
		if (type == SO)
			cub->south = ft_strdup(content);
		if (type == WE)
			cub->west = ft_strdup(content);
		if (type == EA)
			cub->east = ft_strdup(content);
		if ((type == EA || type == NO || type == SO || type == WE)
			&& validate_texture(content) == FAIL)
			return (FAIL);
		if ((type == F || type == C) && get_color(content, type, cub) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	check_id_duplicates(int type, t_cub *cub, char **words)
{
	if (type && words[2])
		return (err(EXTRA_CONTENT), FAIL);
	if (type == NO && cub->north)
		return (err(MULTI_WALL_ID), FAIL);
	if (type == SO && cub->south)
		return (err(MULTI_WALL_ID), FAIL);
	if (type == WE && cub->west)
		return (err(MULTI_WALL_ID), FAIL);
	if (type == EA && cub->east)
		return (err(MULTI_WALL_ID), FAIL);
	if (type == F && cub->floor.r != -1)
		return (err(MULTI_COLOR_ID), FAIL);
	if (type == C && cub->ceiling.r != -1)
		return (err(MULTI_COLOR_ID), FAIL);
	else
		return (SUCCESS);
}

int	label_identifiers(char *id)
{
	if (id)
	{
		if (!ft_strcmp("NO\0", id) || !ft_strcmp("NO\n", id))
			return (NO);
		if (!ft_strcmp("SO\0", id) || !ft_strcmp("SO\n", id))
			return (SO);
		if (!ft_strcmp("WE\0", id) || !ft_strcmp("WE\n", id))
			return (WE);
		if (!ft_strcmp("EA\0", id) || !ft_strcmp("EA\n", id))
			return (EA);
		if (!ft_strcmp("F\0", id) || !ft_strcmp("F\n", id))
			return (F);
		if (!ft_strcmp("C\0", id) || !ft_strcmp("C\n", id))
			return (C);
	}
	return (NONE);
}
