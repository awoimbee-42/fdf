/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:00:07 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/23 12:18:31 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate2d(double *vert1, double *vert2, double theta)
{
	double	cos_;
	double	sin_;

	cos_ = cos(theta);
	sin_ = sin(theta);
	*vert1 = *vert1 * cos_ - *vert2 * sin_;
	*vert2 = *vert2 * cos_ + *vert1 * sin_;
}

/*
** Function that uses rotate 2D to calculate pitch then yaw then roll
*/

void		rotate(t_vertex *vert, t_vertex *rot)
{
	rotate2d(&vert->z, &vert->x, rot->y);
	rotate2d(&vert->x, &vert->y, rot->z);
	rotate2d(&vert->x, &vert->z, rot->x);
}

int		get_rgb(t_uchar *rgb, float zh, t_map *map)
{
	float		coeff;
	int			color;
	int			tmp;

	color = 0;
	coeff = (zh + 1.);
	tmp = coeff * rgb[0] > 255 ? 255 : coeff * rgb[0];
	color |= (tmp << 16);
	tmp = (coeff * rgb[1]) > 255 ? 255 : (coeff * rgb[1]);
	color |= (tmp << 8);
	tmp = (coeff * rgb[2]) > 255 ? 255 : (coeff * rgb[2]);
	color |= tmp;
	//fprintf(stderr, "%f\t", coeff);
	return (color);
}

static void	actually_render(t_coords pos, t_map *map, t_vertices *buff, t_data *data)
{
	float		fov;
	t_vertex	vert;
	t_coords	px;

	while (++pos.y < map->size.y)
	{
		if (!(buff->verts[pos.y] = malloc(map->size.x * sizeof(t_coords))))
			msg_exit("cannot allocate enough memory.", 0);
		pos.x = 0;
		while (map->heightmap[pos.y][pos.x] != INT_MIN)
		{
			vert.x = (pos.x - (map->size.x / 2.)) / map->size.x * data->zoom;
			vert.y = (pos.y - (map->size.x / 2.)) / map->size.x * data->zoom;
			vert.z = (map->heightmap[pos.y][pos.x] - map->mean) / map->delta * -1 * data->zoom;
			px.color = get_rgb(data->rgb, vert.z / data->zoom, map);
			rotate(&vert, &data->rot);
			fov = tan(1.22173047/2); //fov = 70
			px.x = (int)((vert.x * fov) + (WIN_WIDTH / 2.));
			px.y = (int)((vert.z * fov) + (WIN_HEIGHT / 2.));
			normalize_to_window(&px);
			buff->verts[pos.y][pos.x] = px;
			pos.x++;
		}
		while (pos.x <= map->size.x)
			buff->verts[pos.y][pos.x++].x = INT_MIN;
	}
}

void	render(t_mlx *mlx, t_map *map, t_data *data)
{
	t_coords	pos;
	t_vertices	buffer;

	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);
	if (!(buffer.verts = malloc(map->size.y * sizeof(t_coords*))))
		msg_exit("cannot allocate enough memory.", 0);
	pos.y = -1;
	actually_render(pos, map, &buffer, data);
	draw_all_lines(&buffer, map->size.y, mlx->img.data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}
