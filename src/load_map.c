/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:00:12 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 22:33:25 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_map(int fd, t_cub *cub, char *cub_path)
{
	check_map_element(fd, cub);
	if (cub->map_info.height == 0)
		print_error("Map element doesn't exist");
	if (cub->player_count != 1)
		print_error("Start position doesn't exist");
	set_map_array(cub, cub_path);
	if (is_closed_map(cub) == INVALID)
		print_error("Map is not closed");
	update_starting_position(cub);
}

void	check_map_element(int fd, t_cub *cub)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n')
		{
			if (cub->map_start == 1)
				cub->map_end = 1;
		}
		else if (is_map_character(line) == TRUE && count_player(line, cub) < 2)
		{
			if (cub->map_end == 1)
				print_error("Map is seperated by empty lines");
			cub->map_start = 1;
			update_mapsize(line, cub);
		}
		else
			print_error("Wrong map character");
		free(line);
	}
	close(fd);
}

int	is_map_character(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (line[index] == '1' || line[index] == '0' || line[index] == ' ' || \
			line[index] == 'N' || line[index] == 'S' || line[index] == 'W' || \
			line[index] == 'E')
			index++;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	count_player(char *line, t_cub *cub)
{
	int	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (line[index] == 'N' || line[index] == 'S' || line[index] == 'W' || \
			line[index] == 'E')
			cub->player_count++;
		index++;
	}
	if (cub->player_count > 1)
		print_error("Start position must be one");
	return (cub->player_count);
}

void	update_mapsize(char *line, t_cub *cub)
{
	cub->map_info.height++;
	if (cub->map_info.width < (int)ft_strlen(line))
		cub->map_info.width = (int)ft_strlen(line);
}
