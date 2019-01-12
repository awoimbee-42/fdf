/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:26 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/27 15:50:43 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_higrad(t_vertices p0, t_vertices p1, int *img, int win_w)
{
	t_vertices	delta;
	int			way_x;
	int			error;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	way_x = 1;
	if (delta.x < 0 && (delta.x *= -1))
		way_x = -1;
	error = 2 * delta.x - delta.y;
	while (p0.y < p1.y)
	{
		img[(p0.y * win_w + p0.x)] =
		p0.color > p1.color ? p0.color : p1.color;
		if (error > 0)
		{
			p0.x += way_x;
			error -= 2 * delta.y;
		}
		error += 2 * delta.x;
		++p0.y;
	}
}

static void	draw_line_lograd(t_vertices p0, t_vertices p1, int *img, int win_w)
{
	t_vertices	delta;
	int			way_y;
	int			error;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	way_y = 1;
	if (delta.y < 0 && (delta.y *= -1))
		way_y = -1;
	error = 2 * delta.y - delta.x;
	while (p0.x < p1.x)
	{
		img[(p0.y * win_w + p0.x)] =
			p0.color > p1.color ? p0.color : p1.color;
		if (error > 0)
		{
			p0.y += way_y;
			error -= 2 * delta.x;
		}
		error += 2 * delta.y;
		++p0.x;
	}
}

static void	draw_line(t_vertices p0, t_vertices p1, int *img, int win_w)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_line_lograd(p1, p0, img, win_w);
		else
			draw_line_lograd(p0, p1, img, win_w);
	}
	else
	{
		if (p0.y > p1.y)
			draw_line_higrad(p1, p0, img, win_w);
		else
			draw_line_higrad(p0, p1, img, win_w);
	}
}

void		draw_all_lines(t_vertices **buffer, int h, int win_w, int *imgdata)
{
	int			x;
	int			y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (buffer[y][++x].x != INT_MIN)
		{
			if (buffer[y][x].x == __INT_MAX__)
				continue ;
			if (y != 0 && buffer[y - 1][x].x != INT_MIN
			&& buffer[y - 1][x].x != __INT_MAX__)
				draw_line(buffer[y][x], buffer[y - 1][x], imgdata, win_w);
			if (x != 0 && buffer[y][x - 1].x != __INT_MAX__)
				draw_line(buffer[y][x], buffer[y][x - 1], imgdata, win_w);
		}
	}
}
