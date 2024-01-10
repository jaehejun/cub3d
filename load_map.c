/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:00:12 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/10 20:21:36 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_map(int fd, t_cub *cub)
{
	check_map_element(fd, cub);

	//dup_map
	//is_surrounded_or_closed();
	
}

void	check_map_element(int fd, t_cub *cub)
{
	char	*line;

	printf("START:%d\n", cub->map_start);
	printf("END:%d\n", cub->map_end);
	while (1)
	{
		line = get_next_line(fd);
		printf("MAP_CHECK:%s", line);
		if (line == NULL) // 끝까지 다 읽음
			break ;
		else if (*line == '\n') // 빈줄(개행만 있는경우)
		{
			if (cub->map_start == 1) // map시작전까지는 넘기고
				cub->map_end = 1; // map시작했는데 개행만나오면 end flag
		}
		else if (is_map_character(line) == TRUE)
		{
			if (cub->map_end == 1) //유효한 맵line 나온이후에 개행이 나왔었는데 다시 맵line이 나온다면
				print_error("Map is seperated by empty lines");
			cub->map_start = 1; // 유효한 맵line이면 start flag
			cub->map.height++;
			printf("WIDTH:%zu HEIGHT:%zu\n", cub->map.width, cub->map.height);
			if (cub->map.width < ft_strlen(line))
				cub->map.width = ft_strlen(line);
		}
		else
			print_error("Wrong map character");
		free(line);
	}
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