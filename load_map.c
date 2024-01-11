/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:00:12 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/11 20:29:25 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_map(int fd, t_cub *cub, char *cub_path)
{
	check_map_element(fd, cub);
	close(fd);
	set_map_array(cub, cub_path);

	//dup_map
	//is_surrounded_or_closed();
	
}

void	check_map_element(int fd, t_cub *cub)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		printf("MAP:%s", line);
		if (line == NULL) // 끝까지 다 읽음
			break ;
		else if (*line == '\n') // 빈줄(개행만 있는경우)
		{
			if (cub->map_start == 1) // map시작전까지는 넘기고
				cub->map_end = 1; // map시작했는데 개행만나오면 end flag
		}
		else if (is_map_character(line) == TRUE && count_player(line, cub) < 2)
		{
			if (cub->map_end == 1) //유효한 맵line 나온이후에 개행이 나왔었는데 다시 맵line이 나온다면
				print_error("Map is seperated by empty lines");
			cub->map_start = 1; // 유효한 맵line이면 start flag
			update_mapsize(line, cub);
		}
		else
			print_error("Wrong map character");
		free(line);
	}
	if (cub->player_count != 1)
		print_error("Start position doesn't exist");
}

int	is_map_character(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\0' && line[index] != '\n')
	{
		if (line[index] == '1' || line[index] == '0' || line[index] == ' ' ||\
			line[index] == 'N' || line[index] == 'S' || line[index] == 'W' ||\
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
		if (line[index] == 'N' || line[index] == 'S' || line[index] == 'W' ||\
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
	printf("WIDTH:%zu HEIGHT:%zu\n", cub->map_info.width, cub->map_info.height);
	if (cub->map_info.width < ft_strlen(line))
		cub->map_info.width = ft_strlen(line);
}

void	set_map_array(t_cub *cub, char *cub_path)
{
	int		fd;
	//char	*line;

	(void)cub;
	fd = open(cub_path, O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
	cub->map_info.map = malloc(sizeof(char *) * cub->map_info.height + 1);
	cub->map_info.map[cub->map_info.height] = NULL;
	set_first_line(fd, cub);
}

void	set_first_line(int fd, t_cub *cub)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		printf("SETTING_LINE:%s", line);
		if (line == NULL)
			break ;
		else if (*line == '\n')
			;
		else if (is_map_character(line) == TRUE)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			printf("WIDTH:%zu\n", cub->map_info.width);
			cub->map_info.map[0] = dup_and_fill_space(line, cub);
			free(line);
			break ;
		}
		free(line);
	}
	line = get_next_line(fd);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	cub->map_info.map[1] = dup_and_fill_space(line, cub);
	printf("FIRST:%s\n", cub->map_info.map[0]);
	printf("LEN:%zu\n", ft_strlen(cub->map_info.map[0]));
	printf("SECOND:%s\n", cub->map_info.map[1]);
	printf("LEN:%zu\n", ft_strlen(cub->map_info.map[1]));
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
	printf("remove nl len:%d\n", len);
	width = cub->map_info.width;
	printf("remove wid:%d\n", width);
	index = 0;
	mapline[width - 1] = '\0';
	while (len-- > 0)
	{
		mapline[index] = line[index];
		printf("mapline[%d]:%d\n", index, mapline[index]);
		index++;
		width--;
	}
	while (width - 1 > 0)
	{
		mapline[index] = '@';
		printf("fill[%d]:%d\n", index, mapline[index]);
		index++;
		width--;
	}
	return (mapline);
}

//int	is_all_space(char *line)
//{
//	int	index;

//	index = 0;
//	while (line[index] != '\0' || line[index] != '\n')
//	{
//		if (line[index] == ' ')
//			index++;
//		else
//			return (FALSE);
//	}
//	return (TRUE);
//}