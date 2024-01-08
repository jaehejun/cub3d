/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:36:59 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/08 15:46:30 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
 
int	main(int argc, char **argv)
{
	t_cub	*scene;

	if (argc != 2)
	{
		print_error("too many arguments!");
		exit(1);
	}
	scene = malloc(sizeof(t_cub));
	if (scene == NULL)
	{
		print_error("null fail");
		exit(1);
	}
	
	load_scene(scene, argv[1]);
	return (0);
}

void	load_scene(t_cub *scene, char *map_path)
{
	int	fd;

	init_scene(scene); //구조체 초기화
	if (check_extension(map_path) == INVALID) // .cub확인
	{
		print_error("Wrong extension");
		exit(1);
	}
	fd = is_exist(map_path); //.cub path open()확인
	if (fd == INVALID)
	{
		print_error("Cannot open file");
		exit(1);
	}
	get_texture(scene, fd); //구조체 texture 채우기
	//check_texture(scene); // texture 중복검사
	//get_map(scene, fd); // 구조체 map 채우기
	close(fd);
}

void	init_scene(t_cub *scene)
{
	scene->no = NULL;
	scene->so = NULL;
	scene->we = NULL;
	scene->ea = NULL;
	scene->start = 0;
	scene->floor[0] = 0;
	scene->floor[1] = 0;
	scene->floor[2] = 0;
	scene->ceiling[0] = 0;
	scene->ceiling[1] = 0;
	scene->ceiling[2] = 0;
	scene->map = NULL;
}

int	is_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (INVALID);
	return (fd);
}

int	check_extension(char *map_path)
{
	int	map_lenth;

	map_lenth = ft_strlen(map_path);
	if (map_lenth < 4)
		return (INVALID);
	if (map_path[map_lenth -1] != 'b')
		return (INVALID);
	if (map_path[map_lenth -2] != 'u')
		return (INVALID);
	if (map_path[map_lenth -3] != 'c')
		return (INVALID);
	if (map_path[map_lenth -4] != '.')
		return (INVALID);
	return (VALID);
}

void	get_texture(t_cub *scene, int fd)
{
	check_elements(fd);
	(void)scene;
	//if (count_texture != 6)
	//	print_error("Wrong number of elements");
}

int	is_identifier(char *line)
{
	//char	**sep;
	int		ret;

	ret = FALSE;
	if (line[0] == 'N' && line[1] == 'O')
		ret = TRUE;
	if (line[0] == 'S' && line[1] == 'O')
		ret = TRUE;
	if (line[0] == 'W' && line[1] == 'E')
		ret = TRUE;
	if (line[0] == 'E' && line[1] == 'A')
		ret = TRUE;
	if (line[0] == 'F')
		ret = TRUE;
	if (line[0] == 'C')
		ret = TRUE;
	//ret = 0;
	//sep = ft_split(line, ' ');
	//if (sep[0][0] == 'N' && sep[0][1] == 'O' && sep[0][2] == '\0')
	//	ret = TRUE;
	//else if (sep[0][0] == 'S' && sep[0][1] == 'O' && sep[0][2] == '\0')
	//	ret = TRUE;
	//else if (sep[0][0] == 'W' && sep[0][1] == 'E' && sep[0][2] == '\0')
	//	ret = TRUE;
	//else if (sep[0][0] == 'E' && sep[0][1] == 'A' && sep[0][2] == '\0')
	//	ret = TRUE;
	//else if (sep[0][0] == 'F' && sep[0][1] == '\0')
	//	ret = TRUE;
	//else if (sep[0][0] == 'C' && sep[0][1] == '\0')
	//	ret = TRUE;
	else
		return (FALSE);
	printf("%d\n", ret);
	//free_two_ptr(sep);
	return (ret);
}

int	is_map_element(char *line)
{
	if (*line == '1')
		return (TRUE);
	else if (*line == '0')
		return (TRUE);
	else if (*line == ' ')
		return (TRUE);
	//else if (*line == 'N')
	//	return (TRUE);
	//else if (*line == 'S')
	//	return (TRUE);
	//else if (*line == 'W')
	//	return (TRUE);
	//else if (*line == 'E')
	//	return (TRUE);
	else
		return (FALSE);
}

void	free_two_ptr(char **str)
{
	int	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	if (len > 1)
	{
		while (len-- > 0)
			free(str[len]);
	}
	free(str);
}

void	check_elements(int fd)
{
	char	*line;
	int		count_texture;

	count_texture = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n')
			;
		else if (is_identifier(line) == TRUE)
		{
			printf("%c%c\n", line[0], line[1]);
			count_texture++;
			if (count_texture > 6)
				print_error("Wrong number of elements");
		}
		else if (is_map_element(line) == TRUE)
		{
			if (count_texture < 6)
				print_error("Map must be the last");
			else
				;
		}
		else
			print_error("Invalid element");
		free(line);
	}
}

void	set_texture(t_cub *scene, char *line)
{
	char	**sep;
	//int		id;
	(void)scene;
	sep = ft_split(line, ' ');
	//id = check_identifier(sep[0]);
	//if (0 <= id && id <= 3)
	//	put_path(scene, sep);
	//else
	//	put_
	if (sep[1] == NULL)
	{
		print_error("Information not exists");
		return ;
	}
	else if (sep[2] != NULL)
	{
		print_error("Too many informations");
	}
}
