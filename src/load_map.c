/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:00:12 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/30 16:47:17 by jaehejun         ###   ########.fr       */
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
		// identifier 뒷부분부터 한줄씩 읽기 시작
		line = get_next_line(fd);
		// 파일끝까지 읽으면 탈출
		if (line == NULL)
			break ;
		// line이 개행만 있는 줄일 때 map_start==1로 맵이시작됐다면 맵이끝났다고 flag올림
		else if (*line == '\n')
		{
			if (cub->map_start == 1)
				cub->map_end = 1;
		}
		// 유효한 char로만 이루어져있는 line인지 확인, player 하나만 있는지 동시에 확인
		else if (is_map_character(line) == TRUE && count_player(line, cub) < 2)
		{
			// map이 시작되고->개행이 나와서 끝났었는데 mapline이 다시 나온거라면 맵이 쪼개져있으니 에러
			if (cub->map_end == 1)
				print_error("Map is seperated by empty lines");
			// map이 시작했음을 알리는 flag 1로 바꿔줌
			cub->map_start = 1;
			// mapsize 업데이트
			update_mapsize(line, cub);
		}
		else
			print_error("Wrong map character");
		free(line);
	}
	// 파일끝까지 읽어서 탈출했다면 close(fd)
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
// player가 1 이상일때 에러처리
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

// 맵의 높이(map[y][x]에서 y값) 1 증가
// 맵의 너비(map[y][x]에서 x값) 이전과 비교해서 최대값으로 업데이트(개행문자까지 count된상태)
void	update_mapsize(char *line, t_cub *cub)
{
	cub->map_info.height++;
	if (cub->map_info.width < (int)ft_strlen(line))
		cub->map_info.width = (int)ft_strlen(line);
}
