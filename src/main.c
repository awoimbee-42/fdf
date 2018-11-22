/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/22 16:36:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}


/*
**	2D rotation of the axis going from the origin to the vertex
**	https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm
*/

static void	rotate2d(double *vert1, double *vert2, double theta)
{
	double	cos_;
	double	sin_;

	cos_ = cos(theta);
	sin_ = sin(theta);
	*vert1 = *vert1 * cos_ - *vert2 * sin_;
	*vert2 = *vert2 * cos_ + *vert1 * sin_;
}

void	rotate(t_vertex *vert, t_vertex *rot) //, double theta_z for rotation around z ?
{
	rotate2d(&vert->x, &vert->z, rot->x); //roll

	//rotate2d(&vert->z, &vert->x, rot->y); //pitch

	rotate2d(&vert->x, &vert->y, rot->z); //yaw
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

void	render(t_mlx *mlx, t_map *map, t_vertex rot)
{
	int			count_w;
	int			count_h;
	t_vertex	vert;
	double		f;
	int			delta_z;
	t_vertices	buffer;
	int			i;

	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);

	int zoom = 500;
	i = 0;
	if (!(buffer.verts = malloc(map->size.y * sizeof(t_coords*))))
		msg_exit("cannot allocate enough memory.", 0);
	delta_z = map->z_max - map->z_min;
	t_coords p1;
	t_coords end = {INT_MIN, INT_MIN};
	count_h = -1;
	while (++count_h < map->size.y)
	{
		if (!(buffer.verts[count_h] = malloc(map->size.x * sizeof(t_coords))))
			msg_exit("cannot allocate enough memory.", 0);
		count_w = 0;
		while (map->heightmap[count_h][count_w] != INT_MIN)
		{
			vert.x = (count_w - (map->size.x / 2.)) / map->size.x * zoom;
			vert.y = (count_h - (map->size.x / 2.)) / map->size.x * zoom;
			vert.z = (map->heightmap[count_h][count_w] - (delta_z / 2.)) / delta_z * -1 * zoom;

			rotate(&vert, &rot);

			f = tan(1.22173047/2); //fov = 70
			p1.x = (int)((vert.x * f) + (WIN_WIDTH / 2.));
			p1.y = (int)((vert.z * f) + (WIN_HEIGHT / 2.));

			normalize_to_window(&p1);
			buffer.verts[count_h][count_w] = p1;
			count_w++;
		}
		buffer.verts[count_h][count_w] = end;
	}
	draw_all_lines(&buffer, map->size.y, mlx->img.data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

int keypress(int keycode, void *param)
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
		data->rot.x += M_PI / 8.;
	else if (keycode == 125)
		data->rot.x -= M_PI / 8.;
	fprintf(stderr, "keypressed: %d\n", keycode);
	render(data->mlx, data->map, data->rot);
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	*map;
	t_data	data;


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
	render(&mlx, map, data.rot); //M_PI/2

	mlx_key_hook (mlx.win, &keypress, &data);

	mlx_loop(mlx.ptr);
	return (0);
}






// #include "fdf.h"

// void	chaos(void *fate)
// {
// 	if (fate == NULL)
// 		exit(EXIT_FAILURE);
// }


// /*
// **	2D rotation of the axis going from the origin to the vertex
// **	https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm
// */

// static void	rotate2d(double *vert1, double *vert2, double theta)
// {
// 	double	cos_;
// 	double	sin_;

// 	cos_ = cos(theta);
// 	sin_ = sin(theta);
// 	*vert1 = *vert1 * cos_ - *vert2 * sin_;
// 	*vert2 = *vert2 * cos_ + *vert1 * sin_;
// }

// void	rotate(t_vertex *vert, t_vertex *rot) //, double theta_z for rotation around z ?
// {
// 	rotate2d(&vert->x, &vert->z, rot->x); //roll

// 	rotate2d(&vert->z, &vert->x, rot->y); //pitch

// 	rotate2d(&vert->x, &vert->y, rot->z); //yaw
// }

// void	render(t_mlx *mlx, t_map *map, t_vertex rot)
// {
// 	int			count_w;
// 	int			count_h;
// 	t_vertex	vert;
// 	double		f;
// 	float		delta_z;
// 	t_vertices	buffer;
// 	int			i;

// 	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
// 	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);


// 	i = 0;
// 	if (!(buffer.verts = malloc(map->size.y * sizeof(t_coords*))))
// 		msg_exit("cannot allocate enough memory.", 0);
// 	delta_z = map->z_max - map->z_min;
// 	t_coords p1;
// 	count_h = -1;
// 	while (++count_h < map->size.y)
// 	{
// 		if (!(buffer.verts[count_h] = malloc(map->size.x * sizeof(t_coords))))
// 			msg_exit("cannot allocate enough memory.", 0);
// 		count_w = 0;
// 		while (map->heightmap[count_h][count_w] != INT_MIN)
// 		{
// 			vert.x = ((count_w - (map->size.x / 2.)) / map->size.x) * 50;
// 			vert.y = ((count_h - (map->size.x / 2.)) / map->size.x) * 50;
// 			vert.z = ((map->heightmap[count_h][count_w] - (delta_z / 2.)) / delta_z * -1) * 50;

// 			rotate(&vert, &rot);

// 			f = tan(M_PI_4/2); //fov
// 			p1.x = (int)((vert.x * f) + (WIN_WIDTH / 2.f));
// 			p1.y = (int)((vert.z * f) + (WIN_HEIGHT / 2.f));

// 			fprintf(stderr, "why? x: %d\t\ty: %d\n", p1.x, p1.y);

// 			buffer.verts[count_h][count_w] = p1;
// 			count_w++;
// 		}
// 		while (count_w < map->size.x)
// 			buffer.verts[count_h][count_w++].x = INT_MIN;
// 	}
// 	draw_all_lines(&buffer, map->size.y, mlx->img.data);
// 	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
// }

// int keypress(int keycode, void *param)
// {
// 	t_data	*data;

// 	data = (t_data*)param;
// 	// yaw
// 	if (keycode == 123)
// 		data->rot.z += M_PI / 8.;
// 	else if (keycode == 124)
// 		data->rot.z -= M_PI / 8.;
// 	// pitch
// 	else if (keycode == 126)
// 		data->rot.x += M_PI / 8.;
// 	else if (keycode == 125)
// 		data->rot.x -= M_PI / 8.;
// 	fprintf(stderr, "keypressed: %d\n", keycode);
// 	render(data->mlx, data->map, data->rot);
// 	return (1);
// }

// int		main(int argc, char **argv)
// {
// 	t_mlx	mlx;
// 	t_map	*map;
// 	t_data	data;


// 	map = malloc(sizeof(t_map));
// 	map->heightmap = NULL;
// 	map = read_map(map, argv[1]);

// 	chaos((mlx.ptr = mlx_init()));
// 	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
// 	data.rot.x = 0;
// 	data.rot.y = 0;
// 	data.rot.z = 0;
// 	data.map = map;
// 	data.mlx = &mlx;
// 	render(&mlx, map, data.rot); //M_PI/2

// 	mlx_key_hook (mlx.win, &keypress, &data);

// 	mlx_loop(mlx.ptr);
// 	return (0);
// }
