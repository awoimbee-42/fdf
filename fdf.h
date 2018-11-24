/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:34 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/24 01:31:18 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>		//perror() strerror()
# include <stdlib.h>	//exit()
# include <fcntl.h>		//open()
# include <unistd.h>	//read() write() close()
# include <math.h>		//cos() sin()

# ifdef __APPLE__
#  define K_AUP 123
#  define K_DWN 124
#  define K_LFT 126
#  define K_RGT 125
#  define K_LEQ 12
#  define K_LEE 14
#  define K_LEW ...
#  define K_LES ...
#  define K_ESC ...
# elif __linux__
#  define K_AUP 65362
#  define K_DWN 65364
#  define K_LFT 65361
#  define K_RGT 65363
#  define K_LEQ 97
#  define K_LEE 101
#  define K_LEW 122
#  define K_LES 115
#  define K_ESC 65307
# endif

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define WIN_HEIGHT 480
# define WIN_WIDTH 480
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

typedef struct	s_coords
{
	int			x;
	int			y;
	int			color;
}				t_coords;

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vertex;

/*
**	Each line of heightmap is terminated by INT_MIN
*/

typedef struct	s_map
{
	int			**heightmap;
	t_coords	size;
	double		delta;
	double		median;
	int			min;
	int			max;
}				t_map;

typedef struct	s_vertices
{
	int			x;
	int			y;
	int			color;
}				t_vertices;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_vertices	**zbuff;
	t_vertex	rot;
	double		zoom;
	int			rgb;
}				t_data;

void			draw_all_lines(t_vertices **buffer, int height, int *data);
void			msg_exit(char *msg, void *data);
t_map			*read_map(t_map *map, char *filename);
void			render(t_mlx *mlx, t_map *map, t_data *data);
void			normalize_to_window(t_coords *point);

#endif
