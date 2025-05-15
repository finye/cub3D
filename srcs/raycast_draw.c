#include "../incl/cub3D.h"

static void	draw_floor(t_cub *cub, t_raycast *ray, int screen_x)
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

static void	draw_ceiling(t_cub *cub, t_raycast *ray, int screen_x)
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

static void	draw_vertical_column(t_cub *cub, t_player *p, t_raycast *ray, int screen_x)
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

static void	cast_single_ray(t_cub *cub, int screen_x)
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
	int			i;
	int			size;
	t_cub		*cub;
	uint32_t	*pixels;

	i = 0;
	cub = (t_cub *)param;
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
