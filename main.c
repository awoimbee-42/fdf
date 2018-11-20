/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 16:01:45 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}

t_map	read_map(char *filename)
{

}

void	render(t_mlx *mlx)
{
	int		count_w;
	int		count_h;

	count_h = -1;
	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.line_s, &mlx->img.endian);


	t_coords p1 = {0, 0};
	t_coords p2 = {350, 350};
	draw_line(p2, p1, mlx->img.data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;


	t_map map = read_map(argv[1]);

	chaos((mlx.ptr = mlx_init()));
	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));
	render(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
