/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:58:32 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/10 15:15:47 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_scene(char *map_path, t_cub *cub)
{
	int	fd;

	init_scene(cub);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
	load_texture(fd, cub);
	printf("F:%d,%d,%d\n", cub->floor.r, cub->floor.g, cub->floor.b);
	printf("F:%d,%d,%d\n", cub->ceiling.r, cub->ceiling.g, cub->ceiling.b);
	//load_map(fd, cub);
	
	close(fd);
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
	cub->map.map = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.start = 0;
	cub->map.pos_x = 0;
	cub->map.pos_y = 0;
	cub->element_count = 0;
	cub->map_start = 0;
	cub->map_end = 0;
}
