#include "../incl/cub3D.h"

void	init_raycast(t_player *p, t_raycast *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->y = 0;
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
