/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:58:32 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 16:01:46 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_scene(char *cub_path, t_cub *cub)
{
	int	fd;

	init_scene(cub);
	fd = open(cub_path, O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
	load_texture(fd, cub);
	load_map(fd, cub, cub_path);
	//close(fd);
}

void	init_scene(t_cub *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->floor.r = 0;
	cub->floor.g = 0;
	cub->floor.b = 0;
	cub->ceiling.r = 0;
	cub->ceiling.g = 0;
	cub->ceiling.b = 0;
	cub->map_info.map = NULL;
	cub->map_info.width = 0;
	cub->map_info.height = 0;
	cub->map_info.start = 0;
	cub->map_info.pos_x = 0;
	cub->map_info.pos_y = 0;
	cub->element_count = 0;
	cub->player_count = 0;
	cub->map_start = 0;
	cub->map_end = 0;
}
