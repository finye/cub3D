#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/incl/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

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

#define TILE_SZ 32

typedef struct s_cub
{
	char	**map;
	char	*path;
	int		fd;
	int		row;
	int		col;
	int		row_count;
}	t_cub;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_map
{
	char		**map_arr;
	int			map_hgt;
	int			map_wdt;
	t_coord		player_coord;
	mlx_t		*mlx;
	mlx_image_t	*render_img;
	double		ray_dir_x;
	double		ray_dir_y;
	double		camera_plane_x;
	double		camera_plane_y;
	double		player_dir_x;
	double		player_dir_y;
	double		rot_speed;
	double		move_speed;
	double		camera_x;
	double		player_pos_x;
	double		player_pos_y;
	int			screen_wdt;
	int			screen_hgt;
}	t_map;

typedef struct s_raycast
{
	int		step_x;
	int		step_y;
	int		map_pos_x;
	int		map_pos_y;
	int		wall_side;
	bool	wall_hit;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		line_hgt;
	int		draw_start;
	int		draw_end;
}	t_raycast;

// clean
void	free_map(t_cub *cub);

// error
void	err(char *msg);

// init
void	init(t_cub *cub, int fd, char *path);

// main
int		open_file(char *file);

// render map
void	render_map(t_map *m);
void	game_keyhook(void *param);
void	cast_all_rays(void *param);
// parse
int		parse_file(t_cub *cub);

#endif
