/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/28 23:34:53 by awoimbee         ###   ########.fr       */
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
	return (1);
}

void	init(t_data *dat, char *filename)
{
	int		i;

	dat->map.heightmap = NULL;
	read_map(&dat->map, filename);
	chaos((dat->mlx.ptr = mlx_init()));
	dat->win_height = 1024;
	dat->win_width = 1280;
	dat->zoom = dat->win_width / 2;
	dat->rgb = 0xFF0000;
	dat->zh = 1.;
	dat->mv = 8.;
	dat->rot.x = M_PI / dat->mv;
	dat->rot.y = 0;
	dat->rot.z = (M_PI * 2) / dat->mv;


	if (!(dat->zbuff = malloc((dat->map.size.y + 1) * sizeof(t_vertices*)))
		|| !(dat->zbuff[0] = malloc((dat->map.size.y + 1) * (dat->map.size.x + 1) * sizeof(t_vertices))))
		msg_exit("cannot allocate enough memory.", 0);
	i = -1;
	while (++i <= dat->map.size.y)
		dat->zbuff[i] = &dat->zbuff[0][i * (dat->map.size.x + 1)];
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
			(data->mv = (float)ft_atoi(argv[++i])) == 0 ?
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

int		exec_render(t_data *d)
{
	render(&d->mlx, &d->map, d);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	*data;

	if (!(data = ft_memalloc(sizeof(t_data))))
		msg_exit("niet. malloc failed", 0);
	if (argc == 1 || argv[1][0] == '-')
		usage();
	init(data, argv[1]);
	read_args(data, argv, argc);
	chaos((data->mlx.win = mlx_new_window(data->mlx.ptr,
		data->win_width, data->win_height, "Give good grade plz")));
	render(&data->mlx, &data->map, data);
	mlx_hook(data->mlx.win, 2, 1L, &keypress, data);
	mlx_loop_hook(data->mlx.ptr, &exec_render, data);
	mlx_loop(data->mlx.ptr);
	return (0);
}
