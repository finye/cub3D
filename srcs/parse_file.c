#include "../incl/cub3D.h"

static void	get_data(t_cub *cub)
{
	int		i;
	char	**words;
	int		id;

	i = -1;
	while (cub->data[++i])
	{
		words = ft_split(cub->data[i], ' ');
		if (!words)
			free_exit(cub, NULL);
		id = label_identifiers(words[0]);
		if (check_id_duplicates(id, cub, words[2]) == FAIL
			|| store_identifiers(words[1], id, cub) == FAIL)
			free_exit(cub, words);
		if (words[0] && !id)
			extra_content(cub, words);
		if (cub->all_ids && !cub->data[i + 1])
			map_section_missing(cub, words);
		if (cub->all_ids && !id && words[0] && store_map(i, cub) == FAIL)
			free_exit(cub, words);
		if (cub->all_ids && !id && words[0] && !store_map(i, cub) == SUCCESS)
			break ;
		free_split(words);
	}
	free_split(words);
}

static int	count_lines(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd);
	if (!line)
	{
		close(cub->fd);
		return (FAIL);
	}
	while (line)
	{
		cub->line_count++;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
	return (SUCCESS);
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
	if (count_lines(cub) == FAIL)
		return (err(EMPTY_FILE), FAIL);
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
