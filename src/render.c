/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:00:07 by awoimbee          #+#    #+#             */
/*   Updated: 2019/06/19 00:01:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

int			get_rgb(int rgb, float zh)
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

static void	do_render(t_vertices pos, t_map *map, t_data *data)
{
	t_vec4		vert;
	t_vertices	px;
	float		tmp_h;

	while (++pos.y < map->size.y)
	{
		pos.x = -1;
		while (map->heightmap[pos.y][++pos.x] != PX_END_OF_LINE)
		{
			tmp_h = ((map->heightmap[pos.y][pos.x] - map->median) / map->delta * -1) * data->zh;
			vert = vec4_newv(
				((float)pos.x - (map->size.x / 2.)) / map->size.y,
				((float)pos.y - (map->size.y / 2.)) / map->size.y, tmp_h, 1);
			vert = vec4_matmul(data->rot_mat, vert);
			px.color = get_rgb(data->rgb, tmp_h / data->zh);
			px.x = (int)((vert.flt.x * data->fov * data->zoom) + (data->win_width / 2.));
			px.y = (int)((vert.flt.z * data->fov * data->zoom) + (data->win_height / 2.));
			if (px.y >= data->win_height
			|| px.x >= data->win_width)
				px.x = PX_OUTSIDE;
			data->zbuff[pos.y][pos.x] = px;
		}
		while (pos.x <= map->size.x)
			data->zbuff[pos.y][pos.x++].x = PX_END_OF_LINE;
	}
}

static void	build_rot_mat(t_data *d)
{
	float		cos[3];
	float		sin[3];

	cos[0] = cosf(d->rot.x);
	cos[1] = cosf(d->rot.y);
	cos[2] = cosf(d->rot.z);
	sin[0] = sinf(d->rot.x);
	sin[1] = sinf(d->rot.y);
	sin[2] = sinf(d->rot.z);
	d->rot_mat[0] = vec4_newv(
			cos[1] * cos[2], cos[2] * sin[0] * sin[1] - cos[0] * sin[2],
			cos[0] * cos[2] * sin[1] + sin[0] * sin[2], 0.f);
	d->rot_mat[1] = vec4_newv(cos[1] * sin[2],
			cos[0] * cos[2] + sin[0] * sin[1] * sin[2],
			cos[0] * sin[1] * sin[2] - cos[2] * sin[0], 0.f);
	d->rot_mat[2] = vec4_newv(-sin[1], cos[1] * sin[0], cos[0] * cos[1], 0.f);
	d->rot_mat[3] = vec4_newv(0.f, 0.f, 0.f, 1.f);
}

void		render(t_mlx *mlx, t_map *map, t_data *data)
{
	t_vertices	pos;

	clock_t t = clock();
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->win_width, data->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
			&mlx->img.line_s, &mlx->img.endian);
	pos.y = -1;
	build_rot_mat(data);
	do_render(pos, map, data);
	draw_all_lines(data->zbuff, map->size.y, data->win_width, mlx->img.data);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	ft_printf(" rendered in %.2fms\r",
		(float)(clock() - t) / CLOCKS_PER_SEC * 1000);
}
