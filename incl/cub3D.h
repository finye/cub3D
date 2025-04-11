#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/incl/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

# define SUCCESS 0
# define FAIL 1
# define ERROR -1

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define BLUE	"\e[34m"
# define END	"\e[0m"

# define FILE_NOT_CUB "Please provide a valid .cub file"
# define FILE_OPEN_ERROR "Couldn't open map file"
# define MALLOC_MAP "Memory allocation for the map failed"
# define MALLOC_MAP_ROW "Failed to store map row"
# define MAP_TOO_BIG "The map is too big"
# define NO_ARG "Path to a valid map file missing"
# define TOO_MANY_ARGS "Too many arguments"

typedef struct s_cub
{
	char	**map;
	char	*path;
	int		fd;
	int		row;
	int		col;
	int		row_count;
}	t_cub;

// clean
void	free_map(t_cub *cub);

// error
void	err(char *msg);

// init
void	init(t_cub *cub, int fd, char *path);

// main
int		open_file(char *file);

// parse
int		parse_file(t_cub *cub);

#endif
