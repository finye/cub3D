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

# define FLOOR 1
# define CEILING 2

# define EXTRA_RGB "Too many RGB values found"
# define FILE_NOT_CUB "Please provide a valid .cub file"
# define FILE_OPEN_ERROR "Couldn't open map file"
# define MALLOC_INPUT_FILE "Memory allocation for the input data failed"
# define MALLOC_FILE_LINE "Failed to store input file line"
# define MAP_TOO_BIG "The map is too big"
# define MAP_MISSING "Map is missing"
# define MAP_WALLS "Map not fully enclosed with walls"
# define MULTI_COLOR_ID "Multiple color identifiers found"
# define MULTI_WALL_ID "Too many wall texture identifiers found"
# define NO_ARG "Path to a valid map file missing"
# define NO_ID "No valid identifier found"
# define NO_TEXTURE_PATH "No path provided for wall texture"
# define NOT_ID "Identifier missing or invalid syntax"
# define TOO_MANY_ARGS "Too many arguments"
# define WRONG_RGB_VALUE "Invalid RGB value(s)"

typedef struct	s_rbg
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_cub
{
	char			**data;
	char			*path;
	int				fd;
	int				line;
	int				col;
	int				line_count;
	int				id_count;
	t_rgb			floor;
	t_rgb			ceiling;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}	t_cub;

// clean
void	free_data(t_cub *cub);
void	free_split(char **split);

// error
void	err(char *msg);

// floor & ceiling
int		set_floor_ceiling(char *id, char *color_info, t_cub *cub);

// init
void	init(t_cub *cub, int fd, char *path);

// main
int		open_file(char *file);

// parse
int		parse_file(t_cub *cub);
int		parse_line(char **split_line, t_cub *cub);

#endif
