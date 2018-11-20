/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:26 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 15:42:28 by awoimbee         ###   ########.fr       */
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

//draw left to right, top to bottom
void	draw_line(t_coords point1, t_coords point2, int *surface)
{
	int		delta_x;
	int		delta_y;
	float	error;
	float	delta_error;


	delta_x = point2.x - point1.x;
	delta_y = point2.x - point1.y;
	error = 0.;


	if (delta_x < 0 && (delta_x *= -1))
		ft_swap_int(&point1.x, &point2.x);
	if (delta_y < 0 && (delta_y *= -1))
		ft_swap_int(&point1.y, &point2.y);


	if (delta_x == 0)
	{
		draw_straight_horiz(point1, point2, surface);
		return ;
	}
	if (delta_y == 0)
	{
		draw_straight_verti(point1, point2, surface);
		return ;
	}

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
