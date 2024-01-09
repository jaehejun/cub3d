/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:58:32 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/09 22:56:38 by jaehejun         ###   ########.fr       */
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
		if (line == NULL) // 파일 끝까지 다 읽음
			break ;
		else if (*line == '\n') // 다른문자없이 개행만 있는경우
			;
		else if (is_identifier(line, cub) == TRUE)
			cub->element_count++;
		else
			print_error("Wrong identifier");
		cub->map_start++;
		free(line);
	}
	if (cub->element_count != 6)
		print_error("Not enough elements");
	if (check_texture_duplicate(cub) == INVALID)
		print_error("Texture path must be different");
}

int	is_identifier(char *line, t_cub *cub)
{
	char	**sep;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		print_error("Failed to malloc");
	printf("sep[0]:%s\n", sep[0]);
	// space만 있는 줄로 파일이 끝나는 경우(   )
	if (sep[0] == NULL) // -> sep[0][0]에 접근하면 안됨
	{
		//free_two_ptr(sep);
		return (FALSE);
	}
	// space + '\n' 만 있는 경우(  '\n')
	else if (sep[0][0] == '\n')
	{
		//free_two_ptr(sep);
		return (FALSE);
	}
	else if (is_wall_texture(sep, cub) == TRUE || is_rgb(sep, cub) == TRUE)
	{
		free_two_ptr(sep);
		return (TRUE);
	}
	else
	{
		//free_two_ptr(sep);
		return (FALSE);
	}
}

int	is_wall_texture(char **sep, t_cub *cub)
{
	if (ft_strlen(sep[0]) == 2 || (ft_strlen(sep[0]) == 3 && sep[0][2] == '\n'))
	{
		if (ft_strncmp(sep[0], "NO", 2) == 0)
			set_texture(sep, &cub->no);
		else if (ft_strncmp(sep[0], "SO", 2) == 0)
			set_texture(sep, &cub->so);
		else if (ft_strncmp(sep[0], "WE", 2) == 0)
			set_texture(sep, &cub->we);
		else if (ft_strncmp(sep[0], "EA", 2) == 0)
			set_texture(sep, &cub->ea);
		else
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	set_texture(char **sep, char **path)
{
	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	if (sep[2] != NULL)
		print_error("Too many informations");
	if (*path != NULL)
		print_error("Identifier already exists");
	*path = ft_strdup(sep[1]);
	if (*path == NULL)
		print_error("Failed to duplicate texture path");
	printf("PATH:%s\n", *path);
}

int	is_rgb(char **sep, t_cub *cub)
{
	if (ft_strlen(sep[0]) == 1 || (ft_strlen(sep[0]) == 2 && sep[0][1] == '\n'))
	{
		if (ft_strncmp(sep[0], "F", 1) == 0)
			set_rgb(sep, &cub->floor);
		else if (ft_strncmp(sep[0], "C", 1) == 0)
			set_rgb(sep, &cub->ceiling);
		else
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	set_rgb(char **sep, t_rgb *fc)
{
	char	**rgb;

	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	if (sep[2] != NULL)
		print_error("Too many informations");
	//split 이후에 인자로 받은 sep free 해야함
	rgb = ft_split(sep[1], ',');
	if (rgb[0] == NULL)
		print_error("rgb[0] == NULL");
	if (rgb[1] == NULL || rgb[2] == NULL)
		print_error("Invalid rgb information");
	if (rgb[3] != NULL)
		print_error("Invalid rgb information");
	fc->r = ft_atoi(rgb[0]);
	fc->g = ft_atoi(rgb[1]);
	fc->b = ft_atoi(rgb[2]);
	if (0 > fc->r || 0 > fc->g || 0 > fc->b ||\
		 255 < fc->r || 255 < fc->g || 255 < fc->b)
		print_error("Out of rgb range");
	free_two_ptr(rgb);
	// rgb free 해야함
}

int	check_texture_duplicate(t_cub *cub)
{
	if (ft_strcmp(cub->no, cub->so) == 0)
		return (INVALID);
	if (ft_strcmp(cub->no, cub->we) == 0)
		return (INVALID);
	if (ft_strcmp(cub->no, cub->ea) == 0)
		return (INVALID);
	if (ft_strcmp(cub->so, cub->we) == 0)
		return (INVALID);
	if (ft_strcmp(cub->so, cub->ea) == 0)
		return (INVALID);
	if (ft_strcmp(cub->we, cub->ea) == 0)
		return (INVALID);
	return (VALID);
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
