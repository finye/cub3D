#include "../incl/cub3D.h"
#include <string.h>

void init_map(t_map *m)
{
	int i;
	char *rows[] = {
		"111111111",
		"100000001",
		"1000P0001",
		"100000001",
		"111111111"
	};

	m->map_hgt = 5;
	m->map_wdt = 10;
	m->map_arr = malloc((m->map_hgt + 1) * sizeof(char *));
	if (!m->map_arr)
	{
		printf("Failed to allocate memory.");
		exit(1);
	}
	m->map_arr[m->map_hgt] = NULL;
	for (i = 0; i < m->map_hgt; i++) {
		m->map_arr[i] = strdup(rows[i]);
	}
	m->img_floor = NULL;
	m->img_player = NULL;
	m->img_wall = NULL;
	m->pos_p = (t_coord){4, 2};
	printf("[m->pos_p.x] = [%d][ m->pos_p.y] = [%d]\n", m->pos_p.x, m->pos_p.y);
}

static void	get_texture(char *path, mlx_image_t **img, t_map *m)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		printf("Failed to load png.");
	*img = mlx_texture_to_image(m->mlx, texture);
	if (!*img)
		printf("Failed to convert texture to image.");
	mlx_delete_texture(texture);
}

static void	draw_floor(t_map *m)
{
	int	row;
	int	col;

	row = 0;
	while (row < m->map_hgt)
	{
		col = 0;
		while (col < m->map_wdt)
		{
			if (mlx_image_to_window(m->mlx, m->img_floor, col * TILE_SZ, row * TILE_SZ) < 0)
				printf("Failed to draw image to window");
			col++;
		}
		row++;
	}
}

static void	draw_image(t_map *m, mlx_image_t *img, int col, int row)
{
	if (mlx_image_to_window(m->mlx, img, col * TILE_SZ, row * TILE_SZ) < 0)
		printf("Failed to draw image on window");
}

static void	parse_map_to_img(t_map *m)
{
	int	row;
	int	col;

	row = 0;
	while (row < m->map_hgt)
	{
		col = 0;
		while (col < m->map_wdt)
		{
			if (m->map_arr[row][col] == 'P')
				draw_image(m, m->img_player, col, row);
			if (m->map_arr[row][col] == '1')
				draw_image(m, m->img_wall, col, row);
			col++;
		}
		row++;
	}
}

static void	move(char pos, char sign, int new_pos, t_map *d)
{
	if (pos == 'x')
	{
		d->pos_p.x = new_pos;
		if (sign == '-')
			d->img_player->instances[0].x -= TILE_SZ;
		else if (sign == '+')
			d->img_player->instances[0].x += TILE_SZ;
	}
	else if (pos == 'y')
	{
		d->pos_p.y = new_pos;
		if (sign == '-')
			d->img_player->instances[0].y -= TILE_SZ;
		else if (sign == '+')
			d->img_player->instances[0].y += TILE_SZ;
	}
	d->map_arr[d->pos_p.y][d->pos_p.x] = 'P';
}

static void	move_player(int new_y, int new_x, t_map *d, char direction)
{
	printf("[new_y] = [%d][new_x] = [%d]\n", new_y, new_x);
	if (d->map_arr[new_y][new_x] != '1')
	{
		d->map_arr[d->pos_p.y][d->pos_p.x] = '0';
		if (direction == 'L')
			move('x', '-', new_x, d);
		else if (direction == 'R')
			move('x', '+', new_x, d);
		else if (direction == 'U')
			move('y', '-', new_y, d);
		else if (direction == 'D')
			move('y', '+', new_y, d);
	}
}

void	game_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*m;

	m = (t_map *)param;
	if (keydata.action == MLX_PRESS)
	{
		ft_printf("[curr_Y] = [%d][curr_x] = [%d]\n", m->pos_p.y, m->pos_p.x);
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			ft_printf("Moi Moi!!\n");
			mlx_close_window(m->mlx);
			return ;
		}
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			move_player(m->pos_p.y, m->pos_p.x -1, m, 'L');
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			move_player(m->pos_p.y, m->pos_p.x +1, m, 'R');
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			move_player(m->pos_p.y +1, m->pos_p.x, m, 'D');
		else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			move_player(m->pos_p.y -1, m->pos_p.x, m, 'U');
	}
}

void	render_map(t_map *m)
{
	init_map(m);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	m->mlx = mlx_init(m->map_wdt * TILE_SZ, m->map_hgt * TILE_SZ, \
					"cub3D", true);
	if (!m->mlx)
		printf("Failed to initialize mlx.");
	get_texture("./textures/floor.png", &m->img_floor, m);
	get_texture("./textures/asteroid.png", &m->img_wall, m);
	get_texture("./textures/player.png", &m->img_player, m);
	draw_floor(m);
	parse_map_to_img(m);
}