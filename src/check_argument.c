/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:36 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/30 15:41:51 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_argument(int argc, char **argv)
{
	int		fd;
	char	*line;

// argc 2개인지(cub3D 프로그램 실행시 인자로 받는 .cub파일이 한개만 있는지 확인)
	if (argc != 2)
		print_error("Wrong number of arguments");
// 인자로 받는 파일이 .cub 확장자인지 확인
	if (check_format(argv[1]) == INVALID)
		print_error("Wrong map format");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
// 파일이 open가능한지 확인하고 gnl로 한번 읽어서 빈파일인지 확인
	line = get_next_line(fd);
	if (line == NULL)
		print_error("Empty file");
	free(line);
// 파일을 끝까지 읽어서 offset 초기화하고 close(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		free(line);
	}
	close(fd);
}

int	check_format(char *cub_path)
{
	int	file_len;

	file_len = ft_strlen(cub_path);
	if (file_len < 4)
		return (INVALID);
	if (cub_path[file_len - 1] != 'b')
		return (INVALID);
	if (cub_path[file_len - 2] != 'u')
		return (INVALID);
	if (cub_path[file_len - 3] != 'c')
		return (INVALID);
	if (cub_path[file_len - 4] != '.')
		return (INVALID);
	return (VALID);
}
