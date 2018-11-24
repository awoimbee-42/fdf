/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:00:07 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/24 01:56:39 by arthur           ###   ########.fr       */
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

int		get_rgb(int rgb, double zh, t_map *map)
{
	double		coeff;
	int			color;
	t_uchar		tmp;

	color = 0;
	coeff = (zh + 0.6) / 1.1; // needs to be a plus
	tmp = coeff * (rgb & 0xFF) > 255 ? 255 : coeff * (rgb & 0xFF);
	color |= tmp;
	tmp = coeff * (rgb & 0xFF00) > 0xFF00 ? 0xFF00 : coeff * (rgb & 0xFF00);
	color |= tmp;
	tmp = coeff * (rgb & 0xFF0000) > 0xFF0000 ? 0xFF0000 : coeff * (rgb & 0xFF0000);
	color |= tmp;
	return (color);
}

static void	actually_render(t_coords pos, t_map *map, t_data *data)
{
	double		fov;
	t_vertex	vert;
	t_vertices	px;

	while (++pos.y < map->size.y)
	{
		pos.x = 0;
		while (map->heightmap[pos.y][pos.x] != INT_MIN)
		{
			vert.x = ((float)pos.x - (map->size.x / 2.)) / (float)map->size.x;
			vert.y = ((float)pos.y - (map->size.y / 2.)) / (float)map->size.y;
			vert.z = (map->heightmap[pos.y][pos.x] - map->median) / map->delta * -1;

			px.color = get_rgb(data->rgb, vert.z, map);
			rotate(&vert, &data->rot);
			if (vert.z < 0)
				px.x = __INT_MAX__;
			fov = tan(1.22173047/2) * data->zoom;
			px.x = (int)((vert.x * fov) + (WIN_WIDTH / 2.));
			px.y = (int)((vert.z * fov) + (WIN_HEIGHT / 2.));
			if (px.y < 0 || px.y >= WIN_HEIGHT || px.x < 0 || px.x >= WIN_HEIGHT)
				px.x = __INT_MAX__;
			data->zbuff[pos.y][pos.x] = px;
			pos.x++;
		}
		while (pos.x <= map->size.x)
			data->zbuff[pos.y][pos.x++].x = INT_MIN;
	}
}

void	render(t_mlx *mlx, t_map *map, t_data *data)
{
	t_coords	pos;

	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);

	pos.y = -1;
	actually_render(pos, map, data);
	draw_all_lines(data->zbuff, map->size.y, mlx->img.data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr,  mlx->img.ptr);
}
