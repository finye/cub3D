/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:47:57 by eelaine           #+#    #+#             */
/*   Updated: 2025/05/16 08:47:59 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static void	free_map(t_cub *cub)
{
	int	i;

	if (!cub->map.arr)
		return ;
	i = 0;
	while (cub->map.arr[i])
	{
		free(cub->map.arr[i]);
		cub->map.arr[i] = NULL;
		i++;
	}
	free(cub->map.arr);
	cub->map.arr = NULL;
}

void	free_paths(t_cub *cub)
{
	if (cub->north)
		free(cub->north);
	if (cub->south)
		free(cub->south);
	if (cub->west)
		free(cub->west);
	if (cub->east)
		free(cub->east);
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
}

void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub->data)
		return ;
	i = 0;
	while (cub->data[i])
	{
		free(cub->data[i]);
		cub->data[i] = NULL;
		i++;
	}
	free(cub->data);
	cub->data = NULL;
}

void	free_exit(t_cub *cub, char **split)
{
	cleanup_textures(cub);
	free_split(split);
	free_paths(cub);
	free_map(cub);
	if (cub->p.mlx)
		mlx_terminate(cub->p.mlx);
	free_cub(cub);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
