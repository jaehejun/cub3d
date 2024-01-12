/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:37:15 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 22:33:14 by jaehejun         ###   ########.fr       */
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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgb	floor;
	t_rgb	ceiling;
	t_map	map_info;
	int		element_count;
	int		player_count;
	int		map_start;
	int		map_end;
}	t_cub;

void	foo(void);

//utils.c
void	print_error(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	free_two_ptr(char **str);
int		count_comma(char *rgb_info);

// check_argument
void	check_argument(int argc, char **argv);
int		check_format(char *cub_path);

// load_scene
void	load_scene(char *cub_path, t_cub *cub);
void	init_scene(t_cub *cub);

// load_texture
void	load_texture(int fd, t_cub *cub);
int		is_identifier(char *line, t_cub *cub);
int		check_texture_duplicate(t_cub *cub);
void	check_texture_file(char *texture_path);

// set_texture_and_rgb
int		is_wall_texture(char **sep, t_cub *cub);
int		is_rgb(char **sep, t_cub *cub);
void	set_texture(char **sep, char **texture);
void	set_rgb(char **sep, t_rgb *fc);
int		check_rgb_value(char **rgb);

// load_map
void	load_map(int fd, t_cub *cub, char *cub_path);
void	check_map_element(int fd, t_cub *cub);
int		is_map_character(char *line);
int		count_player(char *line, t_cub *cub);
void	update_mapsize(char *line, t_cub *cub);

// set_map_array
void	set_map_array(t_cub *cub, char *cub_path);
void	set_first_line(int fd, t_cub *cub);
char	*dup_and_fill_space(char *line, t_cub *cub);
void	set_every_line(int fd, t_cub *cub);

// is_closed_map
int		is_closed_map(t_cub *cub);
int		check_map_from_outside(t_cub *cub);
int		check_map_from_inside(t_cub *cub);
void	update_starting_position(t_cub *cub);

//check_map_from_outsied
int		check_top_end(t_cub *cub);
int		check_bottom_end(t_cub *cub);
int		check_left_end(t_cub *cub);
int		check_right_end(t_cub *cub);

//int		is_all_space(char *line);

#endif
