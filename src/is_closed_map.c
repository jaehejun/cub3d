/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:51:21 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 22:33:02 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_closed_map(t_cub *cub)
{
	if (check_map_from_outside(cub) == INVALID || \
		check_map_from_inside(cub) == INVALID)
		return (INVALID);
	return (VALID);
}

int	check_map_from_inside(t_cub *cub)
{
	int	width;
	int	height;

	height = -1;
	while (cub->map_info.map[++height] != NULL)
	{
		width = -1;
		while (cub->map_info.map[height][++width] != '\0')
		{
			if (cub->map_info.map[height][width] == '0' || \
				cub->map_info.map[height][width] == 'N' || \
				cub->map_info.map[height][width] == 'S' || \
				cub->map_info.map[height][width] == 'W' || \
				cub->map_info.map[height][width] == 'E')
			{
				if (cub->map_info.map[height][width + 1] == ' ' || \
					cub->map_info.map[height][width - 1] == ' ' || \
					cub->map_info.map[height - 1][width] == ' ' || \
					cub->map_info.map[height + 1][width] == ' ')
					return (INVALID);
			}
		}
	}
	return (VALID);
}

void	update_starting_position(t_cub *cub)
{
	int	width;
	int	height;

	height = -1;
	while (cub->map_info.map[++height] != NULL)
	{
		width = -1;
		while (cub->map_info.map[height][++width] != '\0')
		{
			if (cub->map_info.map[height][width] == 'N' || \
				cub->map_info.map[height][width] == 'S' || \
				cub->map_info.map[height][width] == 'W' || \
				cub->map_info.map[height][width] == 'E')
				cub->map_info.start = cub->map_info.map[height][width];
				cub->map_info.pos_x = width;
				cub->map_info.pos_y = cub->map_info.height - height;
		}
	}
}
