/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:48:03 by eelaine           #+#    #+#             */
/*   Updated: 2025/05/16 08:48:04 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

void	extra_content(t_cub *cub, char **words)
{
	if (cub->all_ids && words[0][0] == '0')
	{
		err(WALL_ERROR);
		free_exit(cub, words);
	}
	if (!cub->all_ids && words[0][0] == '1')
	{
		err(MAP_NOT_LAST);
		free_exit(cub, words);
	}
	else if (!cub->all_ids && !ft_isspace(words[0][0]))
	{
		err(EXTRA_CONTENT);
		free_exit(cub, words);
	}
}

void	map_section_missing(t_cub *cub, char **words)
{
	err(MAP_SECTION_MISSING);
	free_exit(cub, words);
}

void	err(char *msg)
{
	printf(RED "Error\n" END);
	if (mlx_errno)
		printf("%s\n", mlx_strerror(mlx_errno));
	else if (msg)
		printf("%s\n", msg);
}
