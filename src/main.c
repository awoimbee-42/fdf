/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/23 12:23:00 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}

void		normalize_to_window(t_coords *point)
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

int		keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	// yaw
	if (keycode == 123)
		data->rot.z += M_PI / 8.;
	else if (keycode == 124)
		data->rot.z -= M_PI / 8.;
	// pitch
	else if (keycode == 126)
		data->rot.y += M_PI / 8.;
	else if (keycode == 125)
		data->rot.y -= M_PI / 8.;
	//fprintf(stderr, "keypressed: %d\n", keycode);
	render(data->mlx, data->map, data);
	return (1);
}

void	fill_color(t_uchar rgb[3])
{
	rgb[0] = 0x0F;
	rgb[1] = 0xFF;
	rgb[2] = 0xFF;
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	*map;
	t_data	data;
	t_uchar	rgb[3];

	fill_color(rgb);
	map = malloc(sizeof(t_map));
	map->heightmap = NULL;
	map = read_map(map, argv[1]);

	chaos((mlx.ptr = mlx_init()));
	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
	data.rot.x = 0;
	data.rot.y = 0;
	data.rot.z = 0;
	data.map = map;
	data.mlx = &mlx;
	data.zoom = 0.5;//WIN_WIDTH / 2;
	data.rgb = rgb;
	render(&mlx, map, &data); //M_PI/2

	mlx_key_hook (mlx.win, &keypress, &data);

	mlx_loop(mlx.ptr);
	return (0);
}
