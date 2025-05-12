#include "../incl/cub3D.h"

static void	validate_args(int ac, char **av)
{
	size_t	len;

	if (ac == 1)
	{
		err(NO_ARG);
		exit(1);
	}
	if (ac > 2)
	{
		err(TOO_MANY_ARGS);
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (len < 5 || !ft_strnstr(&av[1][len - 4], ".cub", 4) ||
			ft_strnstr(&av[1][len - 5], "/.cub", 5))
	{
		err(FILE_NOT_CUB);
		exit(1);
	}
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		err(FILE_OPEN_ERROR);
		exit(1);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	int		fd;
	t_cub	cub;

	validate_args(ac, av);
	fd = open_file(av[1]);
	init(&cub, fd, av[1]);
	if (parse_file(&cub) == FAIL)
		return (FAIL);
	if (validate_map(&cub) == FAIL)
		return (FAIL);
	setup_mlx(&cub.p);
	mlx_loop_hook(cub.p.mlx, &cast_all_rays, &cub);
	mlx_loop_hook(cub.p.mlx, &game_keyhook, &cub);
	mlx_loop(cub.p.mlx);
	mlx_terminate(cub.p.mlx);
	free_exit(&cub, NULL);
	return (SUCCESS);
}
