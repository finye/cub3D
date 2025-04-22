#include "../incl/cub3D.h"

static int	get_data(t_cub *cub)
{
	int		i;
	int		j;
	char	**split_line;

	i = -1;
	while (cub->data[++i])
	{
		split_line = ft_split(cub->data[i], ' ');
		if (!split_line)
		{
			free_data(cub);
			exit(1);
		}
		if (parse_line(split_line, cub) == FAIL)
		{
			free_split(split_line);
			free_data(cub);
			exit(1);
		}
		free_split(split_line);
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
