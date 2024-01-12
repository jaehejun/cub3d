/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_from_outside.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:34:33 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 15:41:09 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_from_outside(t_cub *cub)
{
	if (check_top_end(cub) == INVALID ||check_bottom_end(cub) == INVALID || \
		check_left_end(cub) == INVALID || check_right_end(cub) == INVALID)
		return (INVALID);
	return (VALID);
}

int	check_top_end(t_cub *cub)
{
	int	index;

	index = 0;
	while (index < cub->map_info.width - 1)
	{
		if (cub->map_info.map[0][index] == '1' || \
			cub->map_info.map[0][index] == ' ')
			index++;
		else
			return (INVALID);
	}
	return (VALID);
}

int	check_bottom_end(t_cub *cub)
{
	int	index;

	index = 0;
	while (index < cub->map_info.width - 1)
	{
		if (cub->map_info.map[cub->map_info.height - 1][index] == '1' || \
			cub->map_info.map[cub->map_info.height - 1][index] == ' ')
			index++;
		else
			return (INVALID);
	}
	return (VALID);
}

int	check_left_end(t_cub *cub)
{
	int	index;

	index = 0;
	while (index < cub->map_info.height)
	{
		if (cub->map_info.map[index][0] == '1' || \
			cub->map_info.map[index][0] == ' ')
			index++;
		else
			return (INVALID);
	}
	return (VALID);
}

int	check_right_end(t_cub *cub)
{
	int	index;

	index = 0;
	while (index < cub->map_info.height)
	{
		if (cub->map_info.map[index][cub->map_info.width - 2] == '1' || \
			cub->map_info.map[index][cub->map_info.width - 2] == ' ')
			index++;
		else
			return (INVALID);
	}
	return (VALID);
}
