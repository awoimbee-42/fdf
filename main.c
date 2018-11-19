#include "fdf.h"

int		main(int argc, char **argv)
{
	void	*window;
	void	*x11;

	x11 = mlx_init ();
	window = mlx_new_window(x11, 700, 700, argv[0]);

	mlx_destroy_window(x11, window);


	return (0);
}