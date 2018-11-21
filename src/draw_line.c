/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:26 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/21 17:16:20 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		draw_straight_verti(t_coords p1, t_coords p2, int *surface)
{
	int			way;

	if (p1.y < p2.y)
		way = 1;
	else
		way = -1;
	while (p1.y * way < p2.y)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		p1.y += way;
	}
	return (1);
}

static int		draw_straight_horiz(t_coords p1, t_coords p2, int *surface)
{
	int			way;

	if (p1.x < p2.x)
		way = 1;
	else
		way = -1;
	while (p1.x * way < p2.x)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		p1.x += way;
	}
	return (1);
}

static void		normalize_to_window(t_coords *point)
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

void			draw_line(t_coords p1, t_coords p2, int *surface)
{
	int			delta_x;
	int			delta_y;
	float		error;
	float		delta_error;
	t_coords	way;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	error = 0.;
	way.x = delta_x < 0 ? -1 : 1;
	way.y = delta_y < 0 ? -1 : 1;
	normalize_to_window(&p1);
	normalize_to_window(&p2);
	if (delta_x == 0 && draw_straight_verti(p1, p2, surface))
		return ;
	else if (delta_y == 0 && draw_straight_horiz(p1, p2, surface))
		return ;
	delta_error = delta_y / delta_x;
	while (p1.x * way.x < p2.x * way.x)
	{
		surface[p1.y * WIN_WIDTH + p1.x] = 0xFFFFFF;
		error += delta_error;
		if (error >= 0.5)
		{
			p1.y += way.y;
			error -= 1.;
		}
		p1.x += way.x;
	}
}
