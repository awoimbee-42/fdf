/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/23 20:12:49 by awoimbee         ###   ########.fr       */
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
	// roll
	else if (keycode == 12)
		data->rot.x += M_PI / 8.;
	else if (keycode == 14)
		data->rot.x -= M_PI / 8.;

	//fprintf(stderr, "keypressed: %d\n", keycode);
	render(data->mlx, data->map, data);
	return (1);
}

void	init(t_map *map, t_data *data, t_mlx *mlx, char *filename)
{
	int		i;

	map->heightmap = NULL;
	map = read_map(map, filename);
	chaos((mlx->ptr = mlx_init()));
	chaos((mlx->win = mlx_new_window(mlx->ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
	data->map = map;
	data->mlx = mlx;
	data->zoom = WIN_WIDTH / 2;
	data->rgb = 0xFF0F0F;
	data->rot.x = 0;
	data->rot.y = 0;
	data->rot.z = 0;
	if (!(data->zbuff = malloc((map->size.y + 1) * sizeof(t_vertices*))))
		msg_exit("cannot allocate enough memory.", 0);
	i = -1;
	while (++i <= map->size.y)
		if (!(data->zbuff[i] = malloc((map->size.x + 1) * sizeof(t_vertices))))
			msg_exit("Ougabouga", 0);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_map	*map;
	t_data	*data;

	data = NULL;
	map = NULL;
	mlx = NULL;
	if (!(map = malloc(sizeof(t_map)))
	|| !(data = malloc(sizeof(t_data)))
	|| !(mlx = malloc(sizeof(t_mlx))))
		msg_exit("niet.", 0);
	init(map, data, mlx, argv[1]);

	render(mlx, data->map, data); //M_PI/2

	//data is becoming currupted befor the keydown function is called !

	mlx_key_hook (mlx->win, &keypress, &data);

	mlx_loop(mlx->ptr);
	return (0);
}
