/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:58:32 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/08 23:31:30 by jaehejun         ###   ########.fr       */
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
	//load_map(fd, cub);
	
	close(fd);
}

void	load_texture(int fd, t_cub *cub)
{
	char	*line;

	while (cub->element_count < 6)
	{
		line = get_next_line(fd);
		printf("line:%s", line);
		if (line == NULL)
			break ;
		else if (*line == '\n')
		{
			cub->map_start++;
			printf("map_start: %d\n", cub->map_start);
		}
		else if (is_identifier(line, cub) == TRUE)
		{
			cub->element_count++;
			printf("el_cnt: %d\n", cub->element_count);
			//set_textures(line, cub);
		}
		else
			print_error("Wrong identifier");
		free(line);
	}
	if (cub->element_count != 6)
		print_error("Not enough elements");
}

int	is_identifier(char *line, t_cub *cub)
{
	char	**sep;

	sep = ft_split(line, ' ');
	printf("ADD: %p\n", sep);
	if (sep == NULL)
	{
		printf("SEP is NULL\n");
		return (FALSE);
	}
	if (sep[0] == NULL)
	{
		printf("SEP[0] is NULL\n");
		return (FALSE);
	}
	if (ft_strlen(sep[0]) == 2)
	{
		if (ft_strncmp(sep[0], "NO", 2) == 0)
			cub->identifier = 'N';
		if (ft_strncmp(sep[0], "SO", 2) == 0)
			cub->identifier = 'S';
		if (ft_strncmp(sep[0], "WE", 2) == 0)
			cub->identifier = 'W';
		if (ft_strncmp(sep[0], "EA", 2) == 0)
			cub->identifier = 'E';
	}
	else if (ft_strlen(sep[0]) == 1)
	{
		if (ft_strncmp(sep[0], "F", 1) == 0)
			cub->identifier = 'F';
		if (ft_strncmp(sep[0], "C", 1) == 0)
			cub->identifier = 'C';
	}
	else
		return (FALSE);
	return (TRUE);
}

//int	check_identifier(char *line)
//{
//	char	**sep;

//	sep = ft_split(line, ' ');
//	if (sep[0] == NULL)
//		print_error("Wrong identifier");
//	if (sep[1] == NULL)
//		print_error("Information not exist");
//	if (sep[2] != NULL)
//		print_error("Too many informations");
//}

void	init_scene(t_cub *cub)
{
	cub->identifier = -1;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->f = NULL;
	cub->c = NULL;
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
