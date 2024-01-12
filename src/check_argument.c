/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:36 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 20:49:07 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_argument(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		print_error("Wrong number of arguments");
	if (check_format(argv[1]) == INVALID)
		print_error("Wrong map format");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error("Failed to open file");
	line = get_next_line(fd);
	if (line == NULL)
		print_error("Empty file");
	free(line);
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
