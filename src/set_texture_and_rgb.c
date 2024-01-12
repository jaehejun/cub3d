/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_and_rgb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:24:02 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 22:16:05 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall_texture(char **sep, t_cub *cub)
{
	if (ft_strlen(sep[0]) == 2 || (ft_strlen(sep[0]) == 3 && sep[0][2] == '\n'))
	{
		if (ft_strncmp(sep[0], "NO", 2) == 0)
			set_texture(sep, &cub->no);
		else if (ft_strncmp(sep[0], "SO", 2) == 0)
			set_texture(sep, &cub->so);
		else if (ft_strncmp(sep[0], "WE", 2) == 0)
			set_texture(sep, &cub->we);
		else if (ft_strncmp(sep[0], "EA", 2) == 0)
			set_texture(sep, &cub->ea);
		else
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	set_texture(char **sep, char **path)
{
	int	len;

	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	if (sep[2] != NULL && sep[2][0] != '\n')
		print_error("Too many informations");
	if (*path != NULL)
		print_error("Identifier already exists");
	len = ft_strlen(sep[1]);
	if (sep[1][len - 1] == '\n')
		sep[1][len - 1] = '\0';
	*path = ft_strdup(sep[1]);
	if (*path == NULL)
		print_error("Failed to duplicate texture path");
}

int	is_rgb(char **sep, t_cub *cub)
{
	if (ft_strlen(sep[0]) == 1 || (ft_strlen(sep[0]) == 2 && sep[0][1] == '\n'))
	{
		if (ft_strncmp(sep[0], "F", 1) == 0)
		{
			if (cub->floor.r != -1)
				print_error("Identifier already exists");
			set_rgb(sep, &cub->floor);
		}
		else if (ft_strncmp(sep[0], "C", 1) == 0)
		{
			if (cub->ceiling.r != -1)
				print_error("Identifier already exists");
			set_rgb(sep, &cub->ceiling);
		}
		else
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	set_rgb(char **sep, t_rgb *fc)
{
	char	**rgb;

	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	if (count_comma(sep[1]) != 2)
		print_error("Wrong number of commas");
	if (sep[2] != NULL && sep[2][0] != '\n')
		print_error("Too many informations");
	rgb = ft_split(sep[1], ',');
	if (rgb[0] == NULL)
		print_error("rgb[0] == NULL");
	if (rgb[1] == NULL || rgb[2] == NULL)
		print_error("Invalid rgb information");
	if (rgb[3] != NULL && rgb[3][0] == '\n')
		print_error("Invalid rgb information");
	if (check_rgb_value(rgb) == INVALID)
		print_error("Invalid rgv value");
	fc->r = ft_atoi(rgb[0]);
	fc->g = ft_atoi(rgb[1]);
	fc->b = ft_atoi(rgb[2]);
	if (0 > fc->r || 0 > fc->g || 0 > fc->b || \
		255 < fc->r || 255 < fc->g || 255 < fc->b)
		print_error("Out of rgb range");
	free_two_ptr(rgb);
}

int	check_rgb_value(char **rgb)
{
	int	arr;
	int	index;
	int	len;

	arr = 0;
	len = ft_strlen(rgb[2]);
	if (rgb[2][len - 1] == '\n')
		rgb[2][len - 1] = '\0';
	while (arr < 3)
	{
		index = 0;
		while (rgb[arr][index] != '\0')
		{
			if (rgb[arr][index] < '0' || rgb[arr][index] > '9')
				return (INVALID);
			index++;
		}
		arr++;
	}
	return (VALID);
}
