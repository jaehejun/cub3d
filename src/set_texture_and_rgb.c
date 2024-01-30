/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_and_rgb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:24:02 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/30 16:34:22 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall_texture(char **sep, t_cub *cub)
{
	// sep의 첫번째 문자열길이가 2거나(개행문자 없음) 개행문자 포함해서 3일때
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

	// texture_path가 스페이스밖에 없거나 스페이스+개행만 들어있는 경우
	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	// texture_path 뒤에도 스페이스로 구분된 '\n'이 아닌 문자열이 존재하는 경우
	if (sep[2] != NULL && sep[2][0] != '\n')
		print_error("Too many informations");
	//해당 identifier이 이전에 나와서 이미 경로가 있는 경우
	if (*path != NULL)
		print_error("Identifier already exists");
	len = ft_strlen(sep[1]);
	//path 끝에 개행문자가 있다면 null문자로 바꿔주고 strdup한다
	if (sep[1][len - 1] == '\n')
		sep[1][len - 1] = '\0';
	*path = ft_strdup(sep[1]);
	if (*path == NULL)
		print_error("Failed to duplicate texture path");
}

int	is_rgb(char **sep, t_cub *cub)
{
	// 첫번째 sep문자열 길이가 1이거나(개행문자 없음)개행문자 포함 2이면
	if (ft_strlen(sep[0]) == 1 || (ft_strlen(sep[0]) == 2 && sep[0][1] == '\n'))
	{
		if (ft_strncmp(sep[0], "F", 1) == 0)
		{
			//이미 rgb값이 설정되어있는 경우
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

	//rgb 값이 스페이스밖에 없거나(+파일의 마지막줄) 스페이스+개행만 있을 때
	if (sep[1] == NULL || sep[1][0] == '\n')
		print_error("Information not exists");
	// rgb값 이후에도 스페이스+개행을 제외한 다른 infomration이 있는 경우
	if (sep[2] != NULL && sep[2][0] != '\n')
		print_error("Too many informations");
	// comma 갯수를 세서 2개가 아니면 에러처리함
	if (count_comma(sep[1]) != 2)
		print_error("Wrong number of commas");
	// rgb information을 쉼표를 구분자로 split
	rgb = ft_split(sep[1], ',');
	// information에 쉼표밖에 없는 경우
	if (rgb[0] == NULL || rgb[0][0] == '\n')
		print_error("rgb[0] == NULL");
	// rgb 숫자가 1개밖에 없거나 2개밖에 없는 경우
	if (rgb[1] == NULL || rgb[2] == NULL || rgb[2][0] == '\n')
		print_error("Invalid rgb information");
	if (check_rgb_value(rgb) == INVALID)
		print_error("Invalid rgv value");
	// atoi로 값을 변환-> rgb[2]의 마지막에 개행문자가 있어도 atoi()가 그전까지만 숫자로 바꿔서 상관없음
	fc->r = ft_atoi(rgb[0]);
	fc->g = ft_atoi(rgb[1]);
	fc->b = ft_atoi(rgb[2]);
	// 숫자범위 확인
	if (0 > fc->r || 0 > fc->g || 0 > fc->b || \
		255 < fc->r || 255 < fc->g || 255 < fc->b)
		print_error("Out of rgb range");
	free_two_ptr(rgb);
}

// rgb information의 모든 값이 0~9 숫자인지 먼저 확인
int	check_rgb_value(char **rgb)
{
	int	arr;
	int	index;
	int	len;

	arr = 0;
	// rgb information 마지막 숫자의 끝에 개행이 있는 경우도 있으니 null문자로 바꾸고 확인
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
