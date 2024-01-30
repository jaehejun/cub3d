/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:13:09 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/30 16:59:55 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	foo(void)
{
	system("leaks cub3D");
}
int	main(int argc, char **argv)
{
	t_cub	cub;
	int	i = 0;
	//atexit(foo);
	check_argument(argc, argv);
	load_scene(argv[1], &cub);
	while (cub.map_info.map[i] != NULL)
		printf("%s\n", cub.map_info.map[i++]);

	free(cub.no);
	free(cub.so);
	free(cub.we);
	free(cub.ea);
	free_two_ptr(cub.map_info.map);
	return (0);
}
