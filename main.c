#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx; //Here I first create my struct that will contains all the "MLX stuff"
	int		count_w;
	int		count_h;

	count_h = -1;
	chaos((mlx.ptr = mlx_init()));
	chaos((mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example")));

	mlx.img.ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp, &mlx.img.line_s,
		&mlx.img.endian);
	/*
	 Now just a little example : here is a loop that will draw each pixels that
	 have an odd width in white and the ones that have an even width in black.
	*/
	while (++count_h < WIN_HEIGHT)
	{
		count_w = -1;
		while (++count_w < WIN_WIDTH)
		{
			if (count_w % 2)
				mlx.img.data[count_h * WIN_WIDTH + count_w] = 0xFFFFFF;
			else
				mlx.img.data[count_h * WIN_WIDTH + count_w] = 0;
		}
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
