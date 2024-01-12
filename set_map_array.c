/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:48:35 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 13:57:08 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_array(t_cub *cub, char *cub_path)
{
	int		fd;

	fd = open(cub_path, O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
	cub->map_info.map = malloc(sizeof(char *) * cub->map_info.height + 1);
	cub->map_info.map[cub->map_info.height] = NULL;
	set_first_line(fd, cub);
	set_every_line(fd, cub);
}

void	set_first_line(int fd, t_cub *cub)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n')
			;
		else if (is_map_character(line) == TRUE)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			cub->map_info.map[0] = dup_and_fill_space(line, cub);
			free(line);
			break ;
		}
		free(line);
	}
}

char	*dup_and_fill_space(char *line, t_cub *cub)
{
	char	*mapline;
	int		len;
	int		width;
	int		index;

	mapline = malloc(sizeof(char) * cub->map_info.width);
	if (mapline == NULL)
		print_error("Failed to malloc");
	len = ft_strlen(line);
	width = cub->map_info.width;
	index = 0;
	mapline[width - 1] = '\0';
	while (width - 1 > 0)
	{
		if (len-- > 0)
			mapline[index] = line[index];
		else
			mapline[index] = ' ';
		index++;
		width--;
	}
	return (mapline);
}

void	set_every_line(int fd, t_cub *cub)
{
	char	*line;
	int		index;

	index = 1;
	while (index < cub->map_info.height)
	{
		line = get_next_line(fd);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		cub->map_info.map[index] = dup_and_fill_space(line, cub);
		free(line);
		index++;
	}
	close(fd);
}
