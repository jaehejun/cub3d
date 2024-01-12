/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:13:09 by jaehejun          #+#    #+#             */
/*   Updated: 2024/01/12 17:34:56 by jaehejun         ###   ########.fr       */
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
	load_scene(argv[1], &cub); //parse 어쩌구로 이름 바꾸는게 더 좋음, 읽는 사람이 생각을 덜하기 때문

	free(cub.no);
	free(cub.so);
	free(cub.we);
	free(cub.ea);
	return (0);
}
