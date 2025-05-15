#include "../incl/cub3D.h"

void	init_imgs(t_cub *cub)
{
	cub->north_img = mlx_texture_to_image(cub->p.mlx, cub->north_tex);
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
	{
		err(TEX_TO_IMG_FAIL);
		free_exit(cub, NULL);
	}
	cleanup_textures(cub);
}

mlx_image_t	*get_tex_direction(t_cub *cub, t_player *p, t_raycast *ray)
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

void	draw_texture(t_cub *cub, int screen_x, int y, t_raycast *ray, mlx_image_t *current_texture)
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
