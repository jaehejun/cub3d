/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:13:09 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 12:54:16 by jaehejun         ###   ########.fr       */
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

	//atexit(foo);
	check_argument(argc, argv);
	load_scene(argv[1], &cub);

	free(cub.no);
	free(cub.so);
	free(cub.we);
	free(cub.ea);
	return (0);
}
