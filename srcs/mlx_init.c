#include "../incl/cub3D.h"

static void	set_window_size(t_player *p)
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
