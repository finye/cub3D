#include "../incl/cub3D.h"

static int	label_ids(char *id, char *content, t_cub *cub)
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
	else
		return (NONE);
}

static void	get_data(t_cub *cub)
{
	int		i;
	int		j;
	char	**words;
	int		id_type;

	i = -1;
	while (cub->data[++i])
	{
		words = ft_split(cub->data[i], ' ');
		if (!words)
		{
			free_data(cub);
			exit(1);
		}
		id_type = label_ids(words[0], words[1], cub);
		if (id_type != NONE)
			cub->id_count++;
		if (cub->id_count == 6 && id_type == NONE)
			return (validate_map(words, cub));
		if (parse_line(words, cub) == FAIL)
		{
			free_split(words);
			free_data(cub);
			exit(1);
		}
		free_split(words);
	}
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
			free_data(cub);
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
