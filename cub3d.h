/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:37:15 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/08 20:03:14 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "libft/get_next_line.h"

# define INVALID -1
# define VALID 1
# define TRUE 1
# define FALSE 0

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	char	start; // NSWE -> int로 변경가능
	double	pos_x;
	double	pos_y;
}	t_map;

typedef struct s_cub
{
	char	identifier;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	t_rgb	floor;
	t_rgb	ceiling;
	t_map	map;
	int		element_count;
	int		map_start;
	int		map_end;
}	t_cub;

//utils.c
void	print_error(const char *str);

// check_argument
void	check_argument(int argc, char **argv);
int		check_format(char *map_path);

// load_scene
void	load_scene(char *map_path, t_cub *cub);
void	init_scene(t_cub *cub);
void	load_texture(int fd, t_cub *cub);
int		is_identifier(char *line, t_cub *cub);


//main.c
//void		load_scene(t_cub *scene, char *map_path);
//int			check_extension(char *path);
//int			is_exist(char *path);
//void		get_texture(t_cub *scene, int fd);
//void		free_two_ptr(char **str);
//void		init_scene(t_cub *scene);
//int			is_identifier(char *line);
//int			is_map_char(char *line);
//void		free_two_ptr(char **str);
//void		set_texture(t_cub *scene, char *line);
//void		check_elements(int fd);

#endif
