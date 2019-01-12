/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/12 02:41:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	keycode == K_UP ? data->rot.x += M_PI / data->mv : 0;
	keycode == K_DWN ? data->rot.x -= M_PI / data->mv : 0;
	keycode == K_LFT ? data->rot.z += M_PI / data->mv : 0;
	keycode == K_RGT ? data->rot.z -= M_PI / data->mv : 0;
	keycode == K_A ? data->rot.y += M_PI / data->mv : 0;
	keycode == K_D ? data->rot.y -= M_PI / data->mv : 0;
	keycode == K_W ? data->zoom *= 1.25 : 0;
	keycode == K_S ? data->zoom /= 1.25 : 0;
	keycode == K_Q ? data->zh /= 1.25 : 0;
	keycode == K_E ? data->zh *= 1.25 : 0;
	keycode == K_ESC ? exit(0) : 0;
	render(data->mlx, data->map, data);
	return (1);
}

void	init(t_map *map, t_data *data, t_mlx *mlx, char *filename)
{
	int		i;

	map->heightmap = NULL;
	map = read_map(map, filename);
	chaos((mlx->ptr = mlx_init()));
	data->win_height = 1024;
	data->win_width = 1280;
	data->map = map;
	data->mlx = mlx;
	data->zoom = data->win_width / 2;
	data->rgb = 0xFF0000;
	data->zh = 1.;
	data->mv = 8.;
	data->rot.x = M_PI / data->mv;
	data->rot.y = 0;
	data->rot.z = (M_PI * 2) / data->mv;
	if (!(data->zbuff = malloc((map->size.y + 1) * sizeof(t_vertices*))))
		msg_exit("cannot allocate enough memory.", 0);
	i = -1;
	while (++i <= map->size.y)
		if (!(data->zbuff[i] = malloc((map->size.x + 1) * sizeof(t_vertices))))
			msg_exit("Malloc failed, not enought memory", 0);
}

void	usage(void)
{
	msg_exit("Usage : ./fdf <filename> [-p] [-c] [-z] [-res]\n\
		\t-p precision: precision of rotation calculated as π/p, must be int\n\
		\t-c basecolor: color in capitalized hex w/o \"0x\" (default: FF0000)\n\
		\t-z zoom: dictate size of object, default to data->win_width / 2\n\
		\t-res width height: resolution of window, cannot be under 10", 0);
}

void	read_args(t_data *data, char **argv, int argc)
{
	int		i;

	i = 1;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			(data->mv = (double)ft_atoi(argv[++i])) == 0 ?
			msg_exit("p cannot be equal to 0 !", 0) : 0;
		else if (ft_strcmp(argv[i], "-c") == 0)
			data->rgb = ft_atoi_base(argv[++i], "0123456789ABCDEF");
		else if (ft_strcmp(argv[i], "-z") == 0)
			(data->zoom = ft_atoi(argv[++i])) < 1 ?
			msg_exit("minimum zoom is 1", 0) : 0;
		else if (ft_strcmp(argv[i], "-res") == 0 && i + 2 < argc)
		{
			(data->win_width = ft_atoi(argv[++i])) < 10 ?
			msg_exit("Window width too small ! (%dpx)", &data->win_width) : 0;
			(data->win_height = ft_atoi(argv[++i])) < 10 ?
			msg_exit("Window height too small ! (%dpx)", &data->win_height) : 0;
		}
		else
			usage();
	}
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
		msg_exit("niet. malloc failed", 0);
	if (argc == 1 || argv[1][0] == '-')
		usage();
	init(map, data, mlx, argv[1]);
	read_args(data, argv, argc);
	chaos((mlx->win = mlx_new_window(mlx->ptr,
		data->win_width, data->win_height, "Give good grade plz")));
	render(mlx, data->map, data);
	mlx_hook(mlx->win, 2, 1L, &keypress, data);
	mlx_loop(mlx->ptr);
	return (0);
}
