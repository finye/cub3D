/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsolomon <fsolomon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:44 by fsolomon          #+#    #+#             */
/*   Updated: 2025/05/16 11:52:59 by fsolomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static void	set_player_direction(t_player *p, double dir_x, double dir_y)
{
	p->player_dir_x = dir_x;
	p->player_dir_y = dir_y;
}

static void	set_camera_plane(t_player *p, double plane_x, double plane_y)
{
	p->camera_plane_x = plane_x;
	p->camera_plane_y = plane_y;
}

static void	init_player_direction(t_player *p)
{
	if (p->player_heading == 'N')
	{
		set_player_direction(p, 0.0, -1.0);
		set_camera_plane(p, 0.66, 0.0);
	}
	else if (p->player_heading == 'S')
	{
		set_player_direction(p, 0.0, 1.0);
		set_camera_plane(p, -0.66, 0.0);
	}
	else if (p->player_heading == 'E')
	{
		set_player_direction(p, 1.0, 0.0);
		set_camera_plane(p, 0.0, 0.66);
	}
	else if (p->player_heading == 'W')
	{
		set_player_direction(p, -1.0, 0.0);
		set_camera_plane(p, 0.0, -0.66);
	}
}

void	init_player_data(t_player *p)
{
	p->render_img = NULL;
	p->rot_angle = 0.05;
	p->move_speed = 0.1;
	p->camera_x = 0.0;
	p->player_pos_x = p->player_coord_x + 0.5;
	p->player_pos_y = p->player_coord_y + 0.5;
	p->screen_wdt = 0;
	p->screen_hgt = 0;
	init_player_direction(p);
}
