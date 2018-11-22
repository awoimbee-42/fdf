/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:30:46 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/22 17:54:16 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Returns nb of int read
*/

int				fill_map_line(char **data, size_t l_nb, t_map *map,
														t_coords *mimx)
{
	char		**tmp;
	size_t		data_len;
	int			height;

	tmp = data;
	while (*tmp)
		++tmp;
	if (!(map->heightmap[l_nb] = malloc((tmp - data + 1) * sizeof(int))))
		msg_exit("cannot malloc heightmap line !", 0);
	data_len = 0;
	while (data[data_len])
	{
		height = ft_atoi(data[data_len]);
		map->heightmap[l_nb][data_len] = height;
		map->mean += height;
		mimx->x = height < mimx->x ? height : mimx->x;
		mimx->y = height > mimx->y ? height : mimx->y;
		data_len++;
	}
	map->heightmap[l_nb][data_len] = INT_MIN;
	return (data_len);
}

static size_t	map_height(char *filename)
{
	size_t		line_nb;
	int			fd;
	char		*line;

	if (!(fd = open(filename, O_RDONLY)))
		msg_exit("Cannot open file \"%s\"", filename);
	line_nb = 0;
	while (get_next_line(fd, &line) > 0 && ++line_nb)
		free(line);
	if (line_nb == 0)
		msg_exit("empty file ?", 0);
	if (close(fd) == -1)
		msg_exit("cannot close file", NULL);
	return (line_nb);
}

void			ft_free_tab(char ***tab)
{
	int			i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		++i;
	}
	free(*tab);
}

t_map			*actually_read(t_map *map, int fd, t_coords *minmax)
{
	char		**tab;
	int			full_len;
	size_t		line_nb;
	int			len;
	char		*line;

	line_nb = 0;
	full_len = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = fill_map_line(tab, line_nb, map, minmax);
		if (len > map->size.x)
			map->size.x = len;
		full_len += len;
		++line_nb;
		free(line);
		ft_free_tab(&tab);
	}
	map->mean /= full_len;
	map->delta = minmax->y - minmax->x;
	return (map);
}

t_map			*read_map(t_map *map, char *filename)
{
	int			fd;
	t_coords	minmax;

	map->mean = 0;
	minmax.x = 0;
	minmax.y = 0;
	map->size.y = map_height(filename);
	map->heightmap = malloc(map->size.y * sizeof(int*));
	if (!(fd = open(filename, O_RDONLY)))
		msg_exit("Cannot open file \"%s\"", filename);
	return (actually_read(map, fd, &minmax));
}
