#include "../incl/cub3D.h"

static int	is_tile_wall(t_map *map, double new_pos_x, double new_pos_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;

	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (1);
	if (map->arr[map_y][map_x] == '1')
		return (1);
	return (0);
}

static int	is_move_blocked(t_map *map, double new_pos_x, double new_pos_y)
{
	double	margin;

	margin = 0.1;
	if (is_tile_wall(map, new_pos_x, new_pos_y))
		return (1);
	if (is_tile_wall(map, new_pos_x + margin, new_pos_y))
		return (1);
	if (is_tile_wall(map, new_pos_x - margin, new_pos_y))
		return (1);
	if (is_tile_wall(map, new_pos_x, new_pos_y + margin))
		return (1);
	if (is_tile_wall(map, new_pos_x, new_pos_y - margin))
		return (1);
	return (0);
}

static void	move_player(double dir_x, double dir_y, t_player *p, t_map *map)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = p->player_pos_x + dir_x * p->move_speed;
	new_pos_y = p->player_pos_y + dir_y * p->move_speed;
	if (new_pos_x < 0 || new_pos_y < 0)
		return ;
	if (!is_move_blocked(map, new_pos_x, new_pos_y))
	{
		p->player_pos_x = new_pos_x;
		p->player_pos_y = new_pos_y;
		p->player_coord_x = (int)p->player_pos_x;
		p->player_coord_y = (int)p->player_pos_y;
		printf("Player moved to [%.2f, %.2f]\n", p->player_pos_x, p->player_pos_y);
	}
}

static void	rotate_player(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->player_dir_x;
	old_plane_x = p->camera_plane_x;

	p->player_dir_x  = p->player_dir_x  * cos(rot_speed) - p->player_dir_y * sin(rot_speed);
	p->player_dir_y = old_dir_x * sin(rot_speed) + p->player_dir_y * cos(rot_speed);
	p->camera_plane_x = p->camera_plane_x * cos(rot_speed) - p->camera_plane_y * sin(rot_speed);
	p->camera_plane_y = old_plane_x * sin(rot_speed) + p->camera_plane_y * cos(rot_speed);
}

void	game_keyhook(void *param)
{
	t_cub		*cub;
	t_player	*p;

	cub = (t_cub *)param;
	p = &cub->p;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
	{
		printf("Moi Moi!!\n");
		mlx_close_window(p->mlx);
	}
	if (mlx_is_key_down(p->mlx, MLX_KEY_A))
		move_player(-p->camera_plane_x, -p->camera_plane_y, p, &cub->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
		move_player(p->camera_plane_x, p->camera_plane_y, p, &cub->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_S))
		move_player(-p->player_dir_x, -p->player_dir_y, p, &cub->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_W))
		move_player(p->player_dir_x, p->player_dir_y, p, &cub->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		rotate_player(p, -p->rot_speed);
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		rotate_player(p, p->rot_speed);
}
