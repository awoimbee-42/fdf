#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}

// int		color_to_mess(t_color *col)
// {
// 		return(		col->a << 24
// 				+	col->r << 16
// 				+	col->g << 8
// 				+	col->b << 0);
// }

void	nw_img(void *window, void *x11)
{
	void *img = mlx_new_image(x11, WIDTH, HEIGHT);
	char *data = mlx_get_data_addr(img, 32, WIDTH * 4, ENDIAN);

	int color = (0 << 24) + (255 << 0xF) + (255 << 0x8) + (255);
	for (int i = 0; i < 700; i += 1)
	{
		for (int l = i; l < i * (700 * 4); l += 4)
			ft_memcpy(data + l, &color, 4);
	}
	mlx_put_image_to_window(x11, window, img, 700, 700);
}

int		main(int argc, char **argv)
{
	void	*window;
	void	*x11;

	chaos((x11 = mlx_init ()));
	chaos((window = mlx_new_window(x11, 700, 700, argv[0])));
	//mlx_clear_window(x11, window);





	nw_img(window, x11);


	sleep(10);

	//mlx_loop(window);


	mlx_destroy_window(x11, window);
	return (0);
}
