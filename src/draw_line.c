/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:26 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/21 16:04:14 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_straight_verti(t_coords point1, t_coords point2, int *surface)
{
	int		way;

	if (point1.y < point2.y)
		way = 1;
	else
		way = -1;
	while (point1.y * way < point2.y)
	{
		surface[point1.y * WIN_WIDTH + point1.x] = 0xFFFFFF;
		point1.y += way;
	}
}

static void	draw_straight_horiz(t_coords point1, t_coords point2, int *surface)
{
	int		way;

	if (point1.x < point2.x)
		way = 1;
	else
		way = -1;
	while (point1.x * way < point2.x)
	{
		surface[point1.y * WIN_WIDTH + point1.x] = 0xFFFFFF;
		point1.x += way;
	}
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


//draw left to right, top to bottom ONLY
void		draw_line(t_coords point1, t_coords point2, int *surface)
{
	int		delta_x;
	int		delta_y;
	float	error;
	float	delta_error;


	delta_x = point2.x - point1.x;
	delta_y = point2.x - point1.y;
	error = 0.;

	normalize_to_window(&point1);
	normalize_to_window(&point2);

	if (delta_x == 0 && delta_y == 0)
	{
		surface[point1.y * WIN_WIDTH + point1.x] = 0xFFFFFF;
		return ;
	}
	else if (delta_x == 0)
		delta_error = 0;
		//draw_straight_horiz(point1, point2, surface);
	else if (delta_y == 0)
		delta_error = 1;
		//draw_straight_verti(point1, point2, surface);
	else
		delta_error = delta_y / delta_x;
	while (point1.x < point2.x)
	{
		surface[point1.y * WIN_WIDTH + point1.x] = 0xFFFFFF;
		error += delta_error;
		if (error >= 0.5)
		{
			++point1.y;
			error -= 1.;
		}
		point1.x += 1;
	}
}
