/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:26:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/06/18 23:29:55 by awoimbee         ###   ########.fr       */
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

# define PX_END_OF_LINE	((uint16_t)-1)
# define PX_OUTSIDE		((uint16_t)-2)

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
	float		x;
	float		y;
	float		z;
}				t_vertex;

typedef struct	s_vertices
{
	uint16_t	x;
	uint16_t	y;
	int			color;
}				t_vertices;

typedef struct	s_map
{
	int			**heightmap;
	t_vertices	size;
	float		delta;
	float		median;
	int			min;
	int			max;
}				t_map;


/*
**	fov doesn't really contains the fov but tan(fov / 2)
*/

typedef struct	s_data
{
	t_mlx		mlx;
	t_map		map;
	t_vertices	**zbuff;
	t_vec4		rot_mat[4] __attribute__((aligned(16)));
	t_vertex	rot;
	float		mv;
	float		zoom;
	int			rgb;
	float		zh;
	int			win_height;
	int			win_width;
	float		fov;
}				t_data;

void			draw_all_lines(t_vertices **buffer,
						int h, int win_w, int *imgdata);
t_map			*read_map(t_map *map, char *filename);
void			render(t_mlx *mlx, t_map *map, t_data *data);
void			chaos(void *fate);
void			ft_exit(t_data *data);

#endif
