/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:00:12 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/09 22:21:57 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void	load_map(int fd, t_cub *cub)
//{
	
//	char	*line;

//	printf("MAP_START:%d\n",cub->map_start);
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (line == NULL)
//			break ;
//		else if (*line == '\n')
//			continue ;
//		else if (is_map_character(line) == TRUE)
//		{
//			if (is_only_space(line) == TRUE)
//				cub->map_start++;
//			else
//				break ;
//		}
//		else
//			print_error()
//	}
//}