/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:00:05 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/06 21:00:16 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static int	count_single(const char *s, const char *c)
{
	int	count;
	int	index;

	index = 0;
	count = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c[0] && s[index] != c[1] && (s[index + 1] == c[0] || \
			s[index + 1] == c[1] || s[index + 1] == '\0'))
			count++;
		index++;
	}
	return (count);
}

static char	*single(const char *s, const char *c)
{
	int		index;
	int		num;
	char	*single;

	num = 0;
	while (s[num] != '\0' && s[num] != c[0] && s[num] != c[1])
		num++;
	single = (char *)malloc(sizeof(char) * (num + 1));
	if (single == NULL)
		return (NULL);
	index = 0;
	while (num-- > 0)
	{
		single[index] = s[index];
		index++;
	}
	single[index] = '\0';
	return (single);
}

char	**ft_split(char const *s, const char *c)
{
	int		index;
	char	**all;

	all = (char **)malloc(sizeof(char *) * (count_single(s, c) + 1));
	if (all == NULL)
		return (NULL);
	index = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && (*s == c[0] || *s == c[1]))
			s++;
		if (*s != '\0' && *s != c[0] && *s != c[1])
		{
			all[index++] = single(s, c);
			if (all[index - 1] == 0)
			{
				free_all(all, index);
				return (NULL);
			}
			while (*s != '\0' && *s != c[0] && *s != c[1])
				s++;
		}
	}
	all[index] = NULL;
	return (all);
}
