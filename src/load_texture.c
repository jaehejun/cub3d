/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:22:24 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 20:49:54 by jaehejun         ###   ########.fr       */
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
		else if (*line == '\n')
			;
		else if (is_identifier(line, cub) == TRUE)
			cub->element_count++;
		else
			print_error("Wrong identifier");
		free(line);
	}
	if (cub->element_count != 6)
		print_error("Not enough elements");
	if (check_texture_duplicate(cub) == INVALID)
		print_error("Texture path must be different");
	check_texture_file(cub->no);
	check_texture_file(cub->so);
	check_texture_file(cub->we);
	check_texture_file(cub->ea);
}

int	is_identifier(char *line, t_cub *cub)
{
	char	**sep;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		print_error("Failed to malloc");
	if (sep[0] == NULL)
		return (FALSE);
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
