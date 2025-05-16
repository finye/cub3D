#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/incl/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>

# define SUCCESS 0
# define FAIL 1
# define ERROR -1

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define BLUE	"\e[34m"
# define END	"\e[0m"

# define NONE 0
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F 5
# define C 6

# define EMPTY_FILE "File is empty"
# define EXTRA_CONTENT "File contains extraneous content"
# define EXTRA_RGB "Too many RGB values found"
# define EXTRA_VALUE "Identifier followed by too many values"
# define FILE_NOT_CUB "Please provide a valid .cub file"
# define FILE_OPEN_ERROR "Couldn't open map file"
# define FORBIDDEN_CHARS "Map contains forbidden characters"
# define MALLOC_INPUT_FILE "Memory allocation for the input data failed"
# define MALLOC_FILE_LINE "Failed to store input file line"
# define MALLOC_MAP "Failed to allocate memory for the map"
# define MALLOC_MAP_LINE "Failed to store individual map line"
# define MAP_TOO_BIG "The map is too big"
# define MAP_MISSING "Map is missing"
# define MAP_SECTION_MISSING "Map section missing from input file"
# define MAP_NOT_LAST "Map placed before declaring other identifiers"
# define MAP_WALLS "Map not fully enclosed with walls"
# define MULTI_COLOR_ID "Multiple color identifiers found"
# define MULTI_START "Multiple player starting positions found"
# define MULTI_WALL_ID "Too many wall texture identifiers found"
# define NO_ARG "Path to a valid map file missing"
# define NO_ID "No valid identifier found"
# define NO_CONTENT "Missing content after identifier(s)"
# define NO_PLAYER "Player starting position not found"
# define NO_TEXTURE_PATH "No path provided for wall texture"
# define NOT_ID "Identifier missing or invalid syntax"
# define OUT_OF_BOUNDS "Player starting position out of bounds"
# define TEX_EXT "Wall texture has an invalid extension"
# define TEX_LOAD_FAIL "Failed to load texture png"
# define TEX_TO_IMG_FAIL "Failed to create/resize images"
# define TEX_TRIM_FAIL "Failed to trim texture path"
# define TOO_MANY_ARGS "Too many arguments"
# define WALL_ERROR "Map not fully surrounded by walls"
# define WRONG_RGB_VALUE "Invalid RGB value(s)"

# define MAX_HEIGHT 500
# define MAX_WIDTH 500
# define RES 1024

typedef struct s_rbg
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	char	**arr;
	int		height;
	int		width;
	bool	pos_found;
	char	left;
	char	right;
	char	above;
	char	below;
}	t_map;

typedef struct s_player
{
	int			player_coord_x;
	int			player_coord_y;
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
	char		player_heading;
	int			screen_wdt;
	int			screen_hgt;
}	t_player;

typedef struct s_raycast
{
	int			step_x;
	int			step_y;
	int			map_pos_x;
	int			map_pos_y;
	int			wall_side;
	bool		wall_hit;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			line_hgt;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		tex_pos;
	double		tex_step;
	int			tex_num;
	int			y;
}	t_raycast;

typedef struct s_cub
{
	char			**data;
	char			*path;
	int				fd;
	int				line;
	int				col;
	int				line_count;
	int				id_count;
	int				all_ids;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
	mlx_image_t		*north_img;
	mlx_image_t		*south_img;
	mlx_image_t		*west_img;
	mlx_image_t		*east_img;
	t_map			map;
	t_rgb			floor;
	t_rgb			ceiling;
	t_player		p;
}	t_cub;

// clean
void		free_cub(t_cub *cub);
void		free_exit(t_cub *cub, char **split);
void		free_paths(t_cub *cub);
void		free_split(char **split);

// error
void		err(char *msg);
void		extra_content(t_cub *cub, char **words);
void		map_section_missing(t_cub *cub, char **words);

// floor & ceiling
int			get_color(char *color_info, int location, t_cub *cub);

// init
void		init(t_cub *cub, int fd, char *path);

// main
int			open_file(char *file);

// map
int			store_map(int current_line, t_cub *cub);
int			validate_map(t_cub *cub);

// mlx_init
void		setup_mlx(t_player *p, t_cub *cub);
void		init_player_data(t_player *p);

// parse
int			check_id_duplicates(int type, t_cub *cub, char **words);
int			parse_file(t_cub *cub);
int			label_identifiers(char *id);
int			store_identifiers(char *content, int type, t_cub *cub);

// player movement
void		game_keyhook(void *param);

// raycast_draw
void		cast_all_rays(void *param);

// raycast_textures
void		init_imgs(t_cub *cub);
mlx_image_t	*get_tex_direction(t_cub *cub, t_player *p, t_raycast *ray);
void		draw_texture(t_cub *cub, int screen_x, t_raycast *ray, \
			mlx_image_t *current_texture);

// raycast utils
void		init_raycast(t_player *p, t_raycast *ray);
void		calc_step_and_side_dist(t_player *p, t_raycast *ray);
void		dda_find_wall(t_map *m, t_raycast *ray);
void		calc_wall_dimensions(t_player *p, t_raycast *ray);

//texture
void		cleanup_textures(t_cub *cub);
int			load_all_textures(t_cub *cub);
int			validate_texture(char *content);

#endif
