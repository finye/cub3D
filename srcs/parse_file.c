#include "../incl/cub3D.h"

static void	count_rows(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd);
	while (line)
	{
		cub->row_count++;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}

static void	store_map(t_cub *cub)
{
	char	*line;
	int		i;

	i = 0;
	cub->fd = open_file(cub->path);
	line = get_next_line(cub->fd);
	while (line)
	{
		cub->map[cub->row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!cub->map[cub->row])
		{
			free_map(cub);
			return (err(MALLOC_MAP_ROW));
		}
		while (line[i] != '\0')
			cub->map[cub->row][cub->col++] = line[i++];
		cub->map[cub->row++][cub->col] = '\0';
		i = 0;
		cub->col = 0;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}

int	parse_file(t_cub *cub)
{
	count_rows(cub);
	cub->map = ft_calloc(cub->row_count + 1, sizeof(char *));
	if (!cub->map)
		err(MALLOC_MAP);
	store_map(cub);
	int i = 0;
	printf(GREEN "\nMAP STORED\ncub->map:\n\n" END);
	while (cub->map[i])
	{
		printf("%s", cub->map[i]);
		i++;
	}
	printf("\n\n");
	return (SUCCESS);
}
