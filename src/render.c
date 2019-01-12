/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:00:07 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/27 16:40:07 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate2d(double *c0, double *c1, double theta)
{
	double	cos_;
	double	sin_;
	double	dbl0;
	double	dbl1;

	cos_ = cos(theta);
	sin_ = sin(theta);
	dbl0 = *c0;
	dbl1 = *c1;
	*c0 = dbl0 * cos_ - dbl1 * sin_;
	*c1 = dbl1 * cos_ + dbl0 * sin_;
}

/*
** Function that uses rotate 2D to calculate pitch then yaw then roll
*/

void		rotate(t_vertex *vert, t_vertex *rot)
{
	rotate2d(&vert->y, &vert->z, rot->x);
	rotate2d(&vert->x, &vert->z, rot->y);
	rotate2d(&vert->x, &vert->y, rot->z);
}

int			get_rgb(int rgb, double zh)
{
	int			color;
	int			tmp;
	int			i;
	int			add;

	color = 0;
	add = ((-zh) + 0.5) * 255.;
	add == 0 ? add = 6 : 0;
	i = -1;
	while (++i < 3)
	{
		tmp = ((rgb >> (i * 8)) & 0xFF) + add;
		tmp > 255 ? tmp = 255 : 0;
		color += tmp << (8 * (i));
	}
	return (color);
}

static void	do_render(t_vertices pos, t_map *map, t_data *data, double fov)
{
	t_vertex	vert;
	t_vertices	px;

	while (++pos.y < map->size.y)
	{
		pos.x = -1;
		while (map->heightmap[pos.y][++pos.x] != INT_MIN)
		{
			vert.x = ((float)pos.x - (map->size.x / 2.)) / (float)map->size.y;
			vert.y = ((float)pos.y - (map->size.y / 2.)) / (float)map->size.y;
			vert.z = ((map->heightmap[pos.y][pos.x] - map->median)
				/ map->delta * -1) * data->zh;
			px.color = get_rgb(data->rgb, vert.z / data->zh);
			rotate(&vert, &data->rot);
			px.x = (int)((vert.x * fov) + (data->win_width / 2.));
			px.y = (int)((vert.z * fov) + (data->win_height / 2.));
			if (px.y < 0 || px.y >= data->win_height
			|| px.x < 0 || px.x >= data->win_width)
				px.x = __INT_MAX__;
			data->zbuff[pos.y][pos.x] = px;
		}
		while (pos.x <= map->size.x)
			data->zbuff[pos.y][pos.x++].x = INT_MIN;
	}
}

void		render(t_mlx *mlx, t_map *map, t_data *data)
{
	t_vertices	pos;
	double		fov;

	mlx->img.ptr = mlx_new_image(mlx->ptr, data->win_width, data->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
											&mlx->img.line_s, &mlx->img.endian);
	pos.y = -1;
	fov = tan(1.22173047 / 2.) * data->zoom;
	do_render(pos, map, data, fov);
	draw_all_lines(data->zbuff, map->size.y, data->win_width, mlx->img.data);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}
