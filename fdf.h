/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/12 02:36:03 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# ifdef __APPLE__
#  define K_UP 126
#  define K_DWN 125
#  define K_LFT 123
#  define K_RGT 124
#  define K_Q 12
#  define K_E 14
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_ESC 53
# elif __linux__
#  define K_UP 65362
#  define K_DWN 65364
#  define K_LFT 65361
#  define K_RGT 65363
#  define K_Q 113
#  define K_E 101
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_ESC 65307
# endif




# define INT_MIN -2147483648
# define INT_MAX 2147483647

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

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vertex;

typedef struct	s_vertices
{
	int			x;
	int			y;
	int			color;
}				t_vertices;

typedef struct	s_map
{
	int			**heightmap;
	t_vertices	size;
	double		delta;
	double		median;
	int			min;
	int			max;
}				t_map;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_vertices	**zbuff;
	t_vertex	rot;
	float		mv;
	double		zoom;
	int			rgb;
	float		zh;
	int			win_height;
	int			win_width;
}				t_data;

void			draw_all_lines(t_vertices **buffer,
						int h, int win_w, int *imgdata);
void			msg_exit(char *msg, void *data);
t_map			*read_map(t_map *map, char *filename);
void			render(t_mlx *mlx, t_map *map, t_data *data);
void			chaos(void *fate);
void			ft_exit(t_data *data);

#endif
