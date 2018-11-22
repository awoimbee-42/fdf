/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:34 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/22 19:03:51 by awoimbee         ###   ########.fr       */
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

# define INT_MIN -2147483648
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
	float		delta;
	float		mean;
	int			min;
	int			max;
}				t_map;

typedef struct	s_vertices
{
	t_coords	**verts;
	t_coords	size;
}				t_vertices;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_vertex	rot;
	float		zoom;
	t_uchar		rgb[3];
}				t_data;

void			draw_all_lines(t_vertices *buffer, int height, int *data);
void			msg_exit(char *msg, void *data);
t_map			*read_map(t_map *map, char *filename);

#endif
