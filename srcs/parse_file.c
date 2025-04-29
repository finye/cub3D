#include "../incl/cub3D.h"

static int store_identifiers(char *content, int type, t_cub *cub)
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
		if (type == F || type == C)
		{
			if (get_color(content, type, cub) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

static int	check_id_duplicates(int type, t_cub *cub)
{
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

static int	label_identifiers(char *id)
{
	if (id)
	{
		printf("current identifier: %s\n", id);
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

static void	get_data(t_cub *cub)
{
	int		i;
	char	**words;
	int		id_type;

	i = -1;
	while (cub->data[++i])
	{
		words = ft_split(cub->data[i], ' ');
		if (!words)
			free_exit(cub, NULL);
		id_type = label_identifiers(words[0]);
		if (check_id_duplicates(id_type, cub) == FAIL)
			free_exit(cub, words);
		if (store_identifiers(words[1], id_type, cub) == FAIL)
			free_exit(cub, words);
		if (!cub->all_ids && words[0][0] == '1' && !id_type)
			map_not_last(cub, words);
		if (cub->all_ids && !id_type && words[0][0] == '1' && store_map(i, cub) == FAIL)
			free_exit(cub, words);
		if (cub->all_ids && !id_type && words[0][0] == '1' && !store_map(i, cub))
			break ;
		free_split(words);
	}
	free_split(words);
}

static void	count_lines(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd);
	while (line)
	{
		cub->line_count++;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}

static void	store_input_file(t_cub *cub)
{
	char	*line;
	int		i;

	i = 0;
	cub->fd = open_file(cub->path);
	line = get_next_line(cub->fd);
	while (line)
	{
		cub->data[cub->line] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!cub->data[cub->line])
		{
			free_cub(cub);
			return (err(MALLOC_FILE_LINE));
		}
		while (line[i] != '\0')
			cub->data[cub->line][cub->col++] = line[i++];
		cub->data[cub->line++][cub->col] = '\0';
		i = 0;
		cub->col = 0;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}

int	parse_file(t_cub *cub)
{
	count_lines(cub);
	cub->data = ft_calloc(cub->line_count + 1, sizeof(char *));
	if (!cub->data)
	{
		err(MALLOC_INPUT_FILE);
		return (FAIL);
	}
	store_input_file(cub);
	int i = 0;
	printf(GREEN "\nINPUT DATA STORED\ncub->data:\n\n" END);
	while (cub->data[i])
	{
		printf("%s", cub->data[i]);
		i++;
	}
	printf("\n\n");
	get_data(cub);
	return (SUCCESS);
}
