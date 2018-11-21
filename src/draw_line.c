/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:26 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/21 17:54:21 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	draw_straight_verti(t_coords p1, t_coords p2, int *surface)
{
	int			way;

	way = p1.y < p2.y ? 1 : -1;
	while (p1.y * way < p2.y * way)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		p1.y += way;
	}
	return (1);
}

static int	draw_straight_horiz(t_coords p1, t_coords p2, int *surface)
{
	int			way;

	way = p1.x < p2.x ? 1 : -1;
	while (p1.x * way < p2.x * way)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		p1.x += way;
	}
	return (1);
}

static void	normalize_to_window(t_coords *point)
{
	if (point->x >= WIN_WIDTH)
		point->x = WIN_WIDTH - 1;
	else if (point->x < 0)
		point->x = 0;
	if (point->y >= WIN_HEIGHT)
		point->y = WIN_HEIGHT - 1;
	else if (point->y < 0)
		point->y = 0;
}

static void	draw_line(t_coords p1, t_coords p2, int *surface)
{
	t_coords	delta;
	float		error;
	float		delta_error;
	t_coords	way;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	error = 0.;
	normalize_to_window(&p1);
	normalize_to_window(&p2);
	if ((delta.x == 0 && draw_straight_verti(p1, p2, surface))
		|| (delta.y == 0 && draw_straight_horiz(p1, p2, surface)))
		return ;
	way.x = delta.x < 0 ? -1 : 1;
	way.y = delta.y < 0 ? -1 : 1;
	delta_error = delta.y / delta.x * way.x * way.y;
	while (p1.x * way.x < p2.x * way.x)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		error += delta_error;
		if (error >= 0.5 && error--)
			p1.y += way.y;
		p1.x += way.x;
	}
}

void		draw_all_lines(t_vertices *buffer, int height, int *data)
{
	int			x;
	int			y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (buffer->verts[y][++x].x != INT_MIN)
		{
			if (y + 1 < height)
				draw_line(buffer->verts[y][x], buffer->verts[y + 1][x], data);
			if (buffer->verts[y][x + 1].x != INT_MIN)
				draw_line(buffer->verts[y][x], buffer->verts[y][x + 1], data);
		}
	}
}
