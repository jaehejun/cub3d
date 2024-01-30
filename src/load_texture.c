/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:22:24 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/30 15:55:15 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(int fd, t_cub *cub)
{
	char	*line;

	while (cub->element_count < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n') // 개행만 있는 경우
			;
		else if (is_identifier(line, cub) == TRUE)
			cub->element_count++;
		else
			print_error("Wrong identifier");
		free(line);
	}
	// element_count가 6개 나오기 전에 파일의 끝까지 읽어서 while문 나온다면
	if (cub->element_count != 6)
		print_error("Not enough elements");
	// texture파일 중복검사
	if (check_texture_duplicate(cub) == INVALID)
		print_error("Texture path must be different");
	// texture파일이 open가능한지, 빈파일이 아닌지 체크
	check_texture_file(cub->no);
	check_texture_file(cub->so);
	check_texture_file(cub->we);
	check_texture_file(cub->ea);
}
// .cub의 한 줄(gnl로 읽은 line)을 스페이스 기준으로 split
int	is_identifier(char *line, t_cub *cub)
{
	char	**sep;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		print_error("Failed to malloc");
	// line이 스페이스로만 이루어져있고 이 line이 파일의 마지막 line인 경우(line에 '\n'가 없음)
	if (sep[0] == NULL)
		return (FALSE);
	// line이 스페이스로만 이루어져있고 파일의 마지막 line은 아님(line에 '\n'가 있음)
	else if (sep[0][0] == '\n')
		return (FALSE);
	// texture이거나rgb identifier이라면 해당 함수안에서 에러처리+구조체에 입력
	else if (is_wall_texture(sep, cub) == TRUE || is_rgb(sep, cub) == TRUE)
	{
		free_two_ptr(sep);
		return (TRUE);
	}
	else
		return (FALSE);
}
// texture 파일 중복검사
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
// texture파일이 open가능한지, 빈파일이 아닌지 체크
void	check_texture_file(char *texture_path)
{
	int		texture_fd;
	char	*line;

	texture_fd = open(texture_path, O_RDONLY);
	if (texture_fd == -1)
		print_error("Failed to open texture file");
	line = get_next_line(texture_fd);
	if (line == NULL)
		print_error("Empty texture file");
	free(line);
	close(texture_fd);
}
