#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>		//perror() strerror()
# include <stdlib.h>	//exit()
# include <fcntl.h>		//open()
# include <unistd.h>	//read() write() close()

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define ENDIAN 0
# define BPP 32
# define LINE_SIZE WIDTH * 4


typedef unsigned char	t_uchar;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			line_s;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}				t_mlx;


#endif
