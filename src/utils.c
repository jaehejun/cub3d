/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:24:43 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 20:50:06 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(const char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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

int	count_comma(char *rgb_info)
{
	int	index;
	int	comma;

	index = 0;
	comma = 0;
	while (rgb_info[index] != '\0')
	{
		if (rgb_info[index] == ',')
			comma++;
		index++;
	}
	return (comma);
}
