/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:22:24 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/10 15:10:59 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (check_texture_path(cub) == INVALID)
		print_error("Failed to open texture file");
}

int	is_identifier(char *line, t_cub *cub)
{
	char	**sep;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		print_error("Failed to malloc");
	printf("sep[0]:%s\n", sep[0]);
	// space만 있는 줄로 파일이 끝나는 경우(   )
	if (sep[0] == NULL) // -> sep[0][0]에 접근하면 segfault
		return (FALSE);
	// space + '\n' 만 있는 경우(  '\n')
	else if (sep[0][0] == '\n')
		return (FALSE);
	else if (is_wall_texture(sep, cub) == TRUE || is_rgb(sep, cub) == TRUE)
	{
		free_two_ptr(sep);
		return (TRUE);
	}
	else
		return (FALSE);
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

int	check_texture_path(t_cub *cub)
{
	int	texture_fd;

	texture_fd = open(cub->no, O_RDONLY);
	if (texture_fd == -1)
		return (INVALID);
	close(texture_fd);
	texture_fd = open(cub->so, O_RDONLY);
	if (texture_fd == -1)
		return (INVALID);
	close(texture_fd);
	texture_fd = open(cub->we, O_RDONLY);
	if (texture_fd == -1)
		return (INVALID);
	close(texture_fd);
	texture_fd = open(cub->ea, O_RDONLY);
	if (texture_fd == -1)
		return (INVALID);
	close(texture_fd);
	return (VALID);
}