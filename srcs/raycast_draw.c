#include "../incl/cub3D.h"

void	set_player_direction(t_player *p, double dir_x, double dir_y)
{
	p->player_dir_x = dir_x;
	p->player_dir_y = dir_y;
}
void	set_camera_plane(t_player *p, double plane_x, double plane_y)
{
	p->camera_plane_x = plane_x;
	p->camera_plane_y = plane_y;
}
void	init_player_direction(t_player *p)
{
	if (p->player_heading == 'N')
	{
		set_player_direction(p, 0.0, -1.0);
		set_camera_plane(p, 0.66, 0.0);
	}
	else if(p->player_heading == 'S')
	{
		set_player_direction(p, 0.0, 1.0);
		set_camera_plane(p, -0.66, 0.0);
	}
	else if(p->player_heading == 'E')
	{
		set_player_direction(p, 1.0, 0.0);
		set_camera_plane(p, 0.0, 0.66);
	}
	else if(p->player_heading == 'W')
	{
		set_player_direction(p, -1.0, 0.0);
		set_camera_plane(p, 0.0, -0.66);
	}
}

void	init_player_data(t_player *p)
{
	p->render_img = NULL;
	p->rot_speed = 0.05;
	p->move_speed = 0.1;
	p->camera_x = 0.0;
	p->player_pos_x = p->player_coord_x + 0.5;
	p->player_pos_y = p->player_coord_y + 0.5;
	p->screen_wdt = 0;
	p->screen_hgt = 0;
	init_player_direction(p);
}

int	is_tile_wall(t_map *map, double new_pos_x, double new_pos_y)
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

int	is_move_blocked(t_map *map, double new_pos_x, double new_pos_y)
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

void	move_player(double dir_x, double dir_y, t_player *p, t_map *map)
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

void	rotate_player(t_player *p, double rot_speed)
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

void	init_imgs(t_cub *cub)
{
	printf("REACHED INIT_IMGS\n");
	cub->north_img = mlx_texture_to_image(cub->p.mlx, cub->north_tex);
	if (!cub->north_img)
		printf("ISSUE WITH LOADING NORTH_IMG\n");
	else
		printf("ray->north_img: width:%u\n", cub->north_img->width);
	if (cub->north_img->width != RES || cub->north_img->height != RES)
		mlx_resize_image(cub->north_img, RES, RES);
	cub->south_img = mlx_texture_to_image(cub->p.mlx, cub->south_tex);
	if (cub->south_img->width != RES || cub->south_img->height != RES)
		mlx_resize_image(cub->south_img, RES, RES);
	cub->west_img = mlx_texture_to_image(cub->p.mlx, cub->west_tex);
	if (cub->west_img->width != RES || cub->west_img->height != RES)
		mlx_resize_image(cub->west_img, RES, RES);
	cub->east_img = mlx_texture_to_image(cub->p.mlx, cub->east_tex);
	if (cub->east_img->width != RES || cub->east_img->height != RES)
		mlx_resize_image(cub->east_img, RES, RES);
	if (!cub->north_img || !cub->south_img || !cub->west_img || !cub->east_img)
		printf("SOS TEXTURE TO IMG FAIL\n");
}

void	init_raycast(t_player *p, t_raycast *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_pos_x = (int)p->player_pos_x;
	ray->map_pos_y = (int)p->player_pos_y;
	ray->wall_side = -1;
	ray->wall_hit = false;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray->ray_dir_x = p->ray_dir_x;
	ray->ray_dir_y = p->ray_dir_y;
	if (p->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / p->ray_dir_x);
	if (p->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / p->ray_dir_y);
	ray->line_hgt = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	calc_step_and_side_dist(t_player *p, t_raycast *ray)
{
	if (ray->ray_dir_x  < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->player_pos_x - ray->map_pos_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_pos_x + 1.0 - p->player_pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->player_pos_y - ray->map_pos_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_pos_y + 1.0 - p->player_pos_y) * ray->delta_dist_y;
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
		if (ray->map_pos_y >= 0 && ray->map_pos_y < m->height && ray->map_pos_x >= 0 && ray->map_pos_x < m->width)
		{
			if (m->arr[ray->map_pos_y][ray->map_pos_x] == '1')
				ray->wall_hit = true;
		}
		else
			break;
	}
}

void	calc_wall_dimensions(t_player *p, t_raycast *ray)
{
	if(ray->wall_side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_hgt = (int)(p->screen_hgt / ray->perp_wall_dist);
	ray->draw_start = -ray->line_hgt / 2 + p->screen_hgt / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_hgt / 2 + p->screen_hgt / 2;
	if(ray->draw_end >= p->screen_hgt)
		ray->draw_end = p->screen_hgt - 1;
}

static mlx_image_t	*get_tex_direction(t_cub *cub, t_player *p, t_raycast *ray)
{
	mlx_image_t	*current_texture;

	current_texture = NULL;
	if (ray->wall_side == 1)
	{
		if (ray->ray_dir_y > 0)
			current_texture = cub->north_img;
		else
			current_texture = cub->south_img;
		ray->wall_x = p->player_pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	else
	{
		if (ray->ray_dir_x > 0)
			current_texture = cub->west_img;
		else
			current_texture = cub->east_img;
		ray->wall_x = p->player_pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	return (current_texture);
}

static void draw_texture(t_cub *cub, int screen_x, int y, t_raycast *ray, mlx_image_t *current_texture)
{
	int			tex_y;
	uint32_t	color;
	uint8_t		*pixel;

	if (!current_texture || !current_texture->pixels)
	{
		printf("ISSUE HERE 1\n");
		return ;
	}
	if (ray->tex_x < 0 || ray->tex_x >= (int)current_texture->width)
	{
		printf("wall_x:%f tex_x:%d\n", ray->wall_x, ray->tex_x);
		printf("ISSUE HERE 2\n");
		return ;
	}
 	tex_y = (int)ray->tex_pos & (current_texture->height - 1);
 	ray->tex_pos += ray->tex_step;
 	pixel = &current_texture->pixels[(tex_y * current_texture->width + ray->tex_x) * 4];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	mlx_put_pixel(cub->p.render_img, screen_x, y, color);
}

void	draw_floor(t_cub *cub, t_raycast *ray, int screen_x)
{
	int			y;
	uint32_t	color;

	y = ray->draw_end + 1;
	color = (cub->floor.r << 24 | cub->floor.g << 16 | cub->floor.b << 8 | 0xFF);
	while (y < cub->p.screen_hgt)
	{
		mlx_put_pixel(cub->p.render_img, screen_x, y, color);
		y++;
	}
}
void	draw_ceiling(t_cub *cub, t_raycast *ray, int screen_x)
{
		int			y;
		uint32_t	color;

		y = 0;
		color = (cub->ceiling.r << 24 | cub->ceiling.g << 16 | cub->ceiling.b << 8 | 0xFF);
		while (y < ray->draw_start)
		{
			mlx_put_pixel(cub->p.render_img, screen_x, y, color);
			y++;
		}
}

void	draw_vertical_column(t_cub *cub, t_player *p, t_raycast *ray, int screen_x)
{
	int			y;
	mlx_image_t	*current_texture;

	current_texture = get_tex_direction(cub, p, ray);
	if (!current_texture)
		return ;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)current_texture->width);
	if (ray->wall_side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = current_texture->width - ray->tex_x - 1;
	if (ray->wall_side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = current_texture->width - ray->tex_x - 1;
	ray->tex_step = 1.0 * current_texture->height / ray->line_hgt;
	ray->tex_pos = (ray->draw_start - p->screen_hgt / 2 + ray->line_hgt / 2) * ray->tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
		draw_texture(cub, screen_x, y++, ray, current_texture);
	draw_ceiling(cub, ray, screen_x);
	draw_floor(cub, ray, screen_x);
}
void	cast_single_ray(t_cub *cub, int screen_x)
{
	t_raycast	ray;

	init_raycast(&cub->p, &ray);
	calc_step_and_side_dist(&cub->p, &ray);
	dda_find_wall(&cub->map, &ray);
	calc_wall_dimensions(&cub->p, &ray);
	draw_vertical_column(cub, &cub->p, &ray, screen_x);
}

void	cast_all_rays(void *param)
{
	t_cub		*cub;
	int			i;
	int			size;
	uint32_t	*pixels;

	cub = (t_cub *)param;
	i = 0;
	pixels = (uint32_t *)cub->p.render_img->pixels;
	size = cub->p.render_img->width * cub->p.render_img->height;
	while (i < size)
		 pixels[i++] = 0x000000FF;
	i = 0;
	while (i < cub->p.screen_wdt)
	{
		cub->p.camera_x = 2 * i / (double)cub->p.screen_wdt - 1; // x-coordinate in camera space
		cub->p.ray_dir_x = cub->p.player_dir_x + cub->p.camera_plane_x * cub->p.camera_x;
		cub->p.ray_dir_y = cub->p.player_dir_y + cub->p.camera_plane_y * cub->p.camera_x;
		cast_single_ray(cub, i);
		i++;
	}
}

void	set_window_size(t_player *p)
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
	p->screen_wdt = (int)(width * 2 / 3);
	p->screen_hgt = (int)(height * 2 / 3);
}

void	setup_mlx(t_player *p)
{
	init_player_data(p);
	set_window_size(p);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	p->mlx = mlx_init(p->screen_wdt, p->screen_hgt, "cub3D", true);
	if (!p->mlx)
	{
		printf("Failed to initialize mlx.\n");
		//Todo: free and exit
	}
	p->render_img = mlx_new_image(p->mlx, p->screen_wdt, p->screen_hgt);
	if (!p->render_img)
	{
		printf("Failed to create img.\n");
		//Todo: free and exit
	}
	if (mlx_image_to_window(p->mlx, p->render_img, 0, 0) < 0)
	{
		printf("Error displaying an img to window.\n");
		//Todo: free and exit
	}
}
