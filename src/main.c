/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/21 17:58:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}



/*
**	2D rotation of the axis going from the origin to the vertex
**	https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm
*/

static void	rotate2d(double *vert1, double *vert2, double theta)
{
	double	cos_;
	double	sin_;

	cos_ = cos(theta);
	sin_ = sin(theta);
	*vert1 = *vert1 * cos_ - *vert2 * sin_;
	*vert2 = *vert2 * cos_ + *vert1 * sin_;
}

void	rotate(t_vertex *vert, double theta_x, double theta_y) //, double theta_z for rotation around z ?
{
	rotate2d(&vert->x, &vert->z, theta_y);
	rotate2d(&vert->y, &vert->z, theta_x);
}

void	render(t_mlx *mlx, t_map *map, double theta_x, double theta_y)
{
	int			count_w;
	int			count_h;
	t_vertex	vert;
	double		f;
	int			delta_z;
	t_vertices	buffer;
	int			i;

	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);


	i = 0;
	if (!(buffer.verts = malloc(map->size.y * sizeof(t_coords*))))
		msg_exit("cannot allocate enough memory.", 0);
	delta_z = map->z_max - map->z_min;
	t_coords p1;
	t_coords end = {INT_MIN, INT_MIN};
	count_h = -1;
	while (++count_h < map->size.y)
	{
		if (!(buffer.verts[count_h] = malloc(map->size.x * sizeof(t_coords))))
			msg_exit("cannot allocate enough memory.", 0);
		count_w = 0;
		while (map->heightmap[count_h][count_w] != INT_MIN)
		{
			vert.x = (count_w - (map->size.x / 2.)) / map->size.x;
			vert.y = (count_h - (map->size.x / 2.)) / map->size.x;
			vert.z = (map->heightmap[count_h][count_w] - (delta_z / 2.)) / delta_z;

			rotate(&vert, theta_x, theta_y);

			f = 500; //fov ~ zoom
			p1.x = (int)((vert.x * f) + (WIN_WIDTH / 2.));
			p1.y = (int)((vert.y * f) + (WIN_HEIGHT / 2.));

			buffer.verts[count_h][count_w] = p1;
			count_w++;
		}
		buffer.verts[count_h][count_w] = end;
	}
	draw_all_lines(&buffer, map->size.y, mlx->img.data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->heightmap = NULL;
	map = read_map(map, argv[1]);

	chaos((mlx.ptr = mlx_init()));
	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
	render(&mlx, map, 0, 0); //M_PI/2
	mlx_loop(mlx.ptr);
	return (0);
}
