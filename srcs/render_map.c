#include "../incl/cub3D.h"

void init_map(t_map *m)
{
	int i;
	char *rows[] = {
		"11111111111111111111",
		"10100000000000000001",
		"10000000000000000001",
		"10000010000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000010000001",
		"10000000000000100001",
		"10000000000000000001",
		"11111111111111111111"
	};

	m->map_hgt = 10;
	m->map_wdt = 20;
	m->map_arr = malloc((m->map_hgt + 1) * sizeof(char *));
	if (!m->map_arr)
	{
		printf("Failed to allocate memory.");
		exit(1);
	}
	m->map_arr[m->map_hgt] = NULL;
	i = 0;
	while(i < m->map_hgt)
	{
		m->map_arr[i] = ft_strdup(rows[i]);
		i++;
	}
	m->render_img = NULL;
	m->player_coord = (t_coord){4, 2};
	m->camera_plane_x = 0.0;
	m->camera_plane_y = 0.66;
	m->player_dir_x = 1.0;
	m->player_dir_y = 0.0;
	m->rot_speed = 0.05;
	m->move_speed = 0.1;
	m->camera_x = 0.0;
	m->player_pos_x = m->player_coord.x + 0.5;
	m->player_pos_y = m->player_coord.y + 0.5;
	m->screen_wdt = 0;
	m->screen_hgt = 0;
}

static void	move_player(double dir_x, double dir_y, t_map *m)
{
	double	new_pos_x;
	double	new_pos_y;
	int		map_x;
	int		map_y;

	new_pos_x = m->player_pos_x + dir_x * m->move_speed;
	new_pos_y = m->player_pos_y + dir_y * m->move_speed;
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	if (map_x < 0 || map_x >= m->map_wdt || map_y < 0 || map_y >= m->map_hgt)
		return;
	if (m->map_arr[map_y][map_x] != '1')
	{
		m->player_pos_x = new_pos_x;
		m->player_pos_y = new_pos_y;
		m->player_coord.x = (int)m->player_pos_x;
		m->player_coord.y = (int)m->player_pos_y;
		printf("Player moved to [%.2f, %.2f]\n", m->player_pos_x, m->player_pos_y);
	}
}

void	game_keyhook(void *param)
{
	t_map	*m;
	double	old_dir_x;
	double	old_plane_x;

	m = (t_map *)param;
	old_dir_x = m->player_dir_x;
	old_plane_x = m->camera_plane_x;
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("Moi Moi!!\n");
		mlx_close_window(m->mlx);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		move_player(-m->camera_plane_x, -m->camera_plane_y, m);
	if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		move_player(m->camera_plane_x, m->camera_plane_y, m);
	if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		move_player(-m->player_dir_x, -m->player_dir_y, m);
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		move_player(m->player_dir_x, m->player_dir_y, m);
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
	{
		m->player_dir_x  = m->player_dir_x  * cos(m->rot_speed) - m->player_dir_y * sin(m->rot_speed);
		m->player_dir_y = old_dir_x * sin(m->rot_speed) + m->player_dir_y * cos(m->rot_speed);
		m->camera_plane_x = m->camera_plane_x * cos(m->rot_speed) - m->camera_plane_y * sin(m->rot_speed);
		m->camera_plane_y = old_plane_x * sin(m->rot_speed) + m->camera_plane_y * cos(m->rot_speed);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
	{
		m->player_dir_x  = m->player_dir_x * cos(-(m->rot_speed)) - m->player_dir_y * sin(-(m->rot_speed));
		m->player_dir_y = old_dir_x * sin(-(m->rot_speed)) + m->player_dir_y * cos(-(m->rot_speed));
		m->camera_plane_x = m->camera_plane_x * cos(-(m->rot_speed)) - m->camera_plane_y * sin(-(m->rot_speed));
		m->camera_plane_y = old_plane_x * sin(-(m->rot_speed)) + m->camera_plane_y * cos(-(m->rot_speed));
	}
}

void	init_raycast(t_map *m, t_raycast *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_pos_x = (int)m->player_pos_x;
	ray->map_pos_y = (int)m->player_pos_y;
	ray->wall_side = -1;
	ray->wall_hit = false;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray->ray_dir_x = m->ray_dir_x;
	ray->ray_dir_y = m->ray_dir_y;
	if (m->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / m->ray_dir_x);
	if (m->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / m->ray_dir_y);
	ray->line_hgt = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	calc_step_and_side_dist(t_map *m, t_raycast *ray)
{
	if (ray->ray_dir_x  < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (m->player_pos_x - ray->map_pos_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_pos_x + 1.0 - m->player_pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (m->player_pos_y - ray->map_pos_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_pos_y + 1.0 - m->player_pos_y) * ray->delta_dist_y;
	}
}

void	dda_find_wall(t_map *m, t_raycast *ray)
{
	while (!ray->wall_hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_pos_x += ray->step_x;
			ray->wall_side = 0; // X-side hit vertical wall
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_pos_y += ray->step_y;
			ray->wall_side = 1; // Y-side hit horizontal wall
		}
		if (ray->map_pos_y >= 0 && ray->map_pos_y < m->map_hgt && ray->map_pos_x >= 0 && ray->map_pos_x < m->map_wdt)
		{
			if (m->map_arr[ray->map_pos_y][ray->map_pos_x] == '1')
				ray->wall_hit = true;
		}
		else
			break;
	}
}

void	calc_wall_dimensions(t_map *m, t_raycast *ray)
{
	if(ray->wall_side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_hgt = (int)(m->screen_hgt / ray->perp_wall_dist);
	// lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_hgt / 2 + m->screen_hgt / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_hgt / 2 + m->screen_hgt / 2;
	if(ray->draw_end >= m->screen_hgt)
		ray->draw_end = m->screen_hgt - 1;
}

void	draw_vertical_slice(t_map *m, t_raycast *ray, int screen_x)
{
	uint32_t	color;
	int			y;
	int			ceiling_y;
	int			floor_y;

	if (ray->wall_side == 1)
		color = 0xFF0000FF; // Horizontal wall (Y-side)
	else
		color = 0xF7CAC9FF; // Vertical wall (X-side)
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(m->render_img, screen_x, y, color);
		y++;
	}
	ceiling_y = 0;
	while (ceiling_y < ray->draw_start)
	{
		mlx_put_pixel(m->render_img, screen_x, ceiling_y, 0xB565A7FF);
		ceiling_y++;
	}
	floor_y = ray->draw_end + 1;
	while (floor_y < m->screen_hgt)
	{
		mlx_put_pixel(m->render_img, screen_x, floor_y, 0xFF6F61FF);
		floor_y++;
	}
}

void	cast_single_ray(t_map *m, int screen_x)
{
	t_raycast	ray;

	init_raycast(m, &ray);
	calc_step_and_side_dist(m, &ray);
	dda_find_wall(m, &ray);
	calc_wall_dimensions(m, &ray);
	draw_vertical_slice(m, &ray, screen_x);
}

void cast_all_rays(void *param)
{
	t_map		*m;
	int			i;
	int			size;
	uint32_t	*pixels;

	m = (t_map *)param;
	i = 0;
	pixels = (uint32_t *)m->render_img->pixels;
	size = m->render_img->width * m->render_img->height;
	while (i < size)
		 pixels[i++] = 0x000000FF;
	i = 0;
	while (i <  m->screen_wdt)
	{
		m->camera_x = 2 * i / (double)m->screen_wdt - 1; // x-coordinate in camera space
		m->ray_dir_x = m->player_dir_x + m->camera_plane_x * m->camera_x;
		m->ray_dir_y = m->player_dir_y + m->camera_plane_y * m->camera_x;
		cast_single_ray(m, i);
		i++;
	}
}

void	set_window_size(t_map *m)
{
	mlx_t	*mlx;
	int32_t	width;
	int32_t	height;
	mlx = mlx_init(1, 1, "temp_init", false);
	if (!mlx)
	{
		printf("Failed to initialize mlx.\n");
		//Todo: free and exit
	}
	mlx_get_monitor_size(0, &width, &height);
	mlx_terminate(mlx);
	m->screen_wdt = (int)(width * 2 / 3);
	m->screen_hgt = (int)(height * 2 / 3);
}

void	render_map(t_map *m)
{
	init_map(m);
	set_window_size(m);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	m->mlx = mlx_init(m->screen_wdt, m->screen_hgt, "cub3D", true);
	if (!m->mlx)
	{
		printf("Failed to initialize mlx.\n");
		//Todo: free and exit
	}
	m->render_img = mlx_new_image(m->mlx, m->screen_wdt, m->screen_hgt);
	if (!m->render_img)
	{
		printf("Failed to create img.\n");
		//Todo: free and exit
	}
	if (mlx_image_to_window(m->mlx, m->render_img, 0, 0) < 0)
	{
		printf("Error displaying an img to window.\n");
		//Todo: free and exit
	}
}
