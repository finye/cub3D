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
		if (check_id_duplicates(id, cub, words) == FAIL
			|| store_identifiers(words[1], id, cub) == FAIL)
			free_exit(cub, words);
		if (words[0] && !id)
			extra_content(cub, words);
		if (cub->all_ids && !cub->data[i + 1])
			map_section_missing(cub, words);
		if (cub->all_ids && !id && words[0] && store_map(i, cub) == SUCCESS)
		{
			free_split(words);
			break ;
		}
		else if (cub->all_ids && !id && words[0] && store_map(i, cub) == FAIL)
			free_exit(cub, words);
		free_split(words);
	}
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
	if (load_all_textures(cub) == FAIL)
		return (FAIL);
	if (cub->north_tex)
	{
		printf(GREEN "North texture %s" END, cub->north);
		printf("  - Width: %u\n", cub->north_tex->width);
		printf("  - Height: %u\n", cub->north_tex->height);
		printf("  - Pixels Address: %p\n", cub->north_tex->pixels);
		printf("  - Status:" GREEN "LOADED SUCCESSFULLY\n" END);
	}
	else
		printf("South texture: FAILED TO LOAD\n");
	if (cub->south_tex)
	{
		printf(GREEN "South texture %s" END, cub->south);
		printf("  - Width: %u\n", cub->south_tex->width);
		printf("  - Height: %u\n", cub->south_tex->height);
		printf("  - Pixels Address: %p\n", cub->south_tex->pixels);
		printf("  - Status:" GREEN "LOADED SUCCESSFULLY\n" END);
	}
	else
		printf("South texture: FAILED TO LOAD\n");
	if (cub->west_tex)
	{
		printf(GREEN "West texture %s" END, cub->west);
		printf("  - Width: %u\n", cub->west_tex->width);
		printf("  - Height: %u\n", cub->west_tex->height);
		printf("  - Pixels Address: %p\n", cub->west_tex->pixels);
		printf("  - Status:" GREEN "LOADED SUCCESSFULLY\n" END);
	}
	else
		printf("West texture: FAILED TO LOAD\n");
	if (cub->east_tex)
	{
		printf(GREEN "East texture %s" END, cub->east);
		printf("  - Width: %u\n", cub->east_tex->width);
		printf("  - Height: %u\n", cub->east_tex->height);
		printf("  - Pixels Address: %p\n", cub->east_tex->pixels);
		printf("  - Status:" GREEN "LOADED SUCCESSFULLY\n" END);
	}
	else
		printf("East texture: FAILED TO LOAD\n");
	free_paths(cub);
	return (SUCCESS);
}
