#include "../incl/cub3D.h"

static void	validate_args(int ac, char **av)
{
	size_t	len;

	if (ac == 1)
		err(NO_ARG);
	if (ac > 2)
		err(TOO_MANY_ARGS);
	len = ft_strlen(av[1]);
	if (len < 5 || !ft_strnstr(&av[1][len - 4], ".cub", 4) ||
			ft_strnstr(&av[1][len - 5], "/.cub", 5))
		err(FILE_NOT_CUB);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err(FILE_OPEN_ERROR);
	return (fd);
}

int	main(int ac, char **av)
{
	int		fd;
	t_cub	cub;
	t_map	m;

	validate_args(ac, av);
	fd = open_file(av[1]);
	init(&cub, fd, av[1]);
	parse_file(&cub);
	render_map(&m);
	mlx_loop_hook(m.mlx, &cast_all_rays, &m);
	mlx_loop_hook(m.mlx, &game_keyhook, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	return (0);
}
