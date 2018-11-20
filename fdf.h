/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:34 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 16:01:12 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>		//perror() strerror()
# include <stdlib.h>	//exit()
# include <fcntl.h>		//open()
# include <unistd.h>	//read() write() close()
# include <math.h>		//cos() sin()

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
}				t_coords;

typedef struct	s_map
{
	int			*(coords[3]);
	size_t		line_s;
}				t_map;

void			draw_line(t_coords point1, t_coords point2, int *surface);

#endif
