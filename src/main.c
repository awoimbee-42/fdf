/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 18:15:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}


void	render(t_mlx *mlx, t_map *map)
{
//	int		count_w;
//	int		count_h;

//	count_h = -1;
	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);


	//DO THE 3D STUFF HERE


	//this is just a test
	t_coords p1;
	t_coords p2;
	size_t	index = 0;
	while (map->verts[index].x != __FLT_MAX__)
	{
		p1.x = map->verts[index].x * 20;
		p1.y = map->verts[index].y * 20;
		p2.x = map->verts[index+1].x * 20;
		p2.y = map->verts[index+1].y * 20;
		draw_line(p1, p2, mlx->img.data);
		index++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->verts = NULL;
	map = read_map(map, argv[1]);

	chaos((mlx.ptr = mlx_init()));
	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
	render(&mlx, map);
	mlx_loop(mlx.ptr);
	return (0);
}
