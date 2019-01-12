/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:30:46 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/12 18:38:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Returns nb of int read
*/

int				fill_map_line(char **data, t_map *map)
{
	char		**tmp;
	size_t		data_len;
	int			height;

	tmp = data;
	while (*tmp)
		++tmp;
	if (!(map->heightmap[map->size.y] = malloc((tmp - data + 1) * sizeof(int))))
		msg_exit("cannot malloc heightmap line !", 0);
	data_len = 0;
	while (data[data_len])
	{
		height = ft_atoi(data[data_len]);
		if (height == 0 && *data[data_len] != '0')
			msg_exit("Invalid file ! read : %s", data[data_len]);
		map->heightmap[map->size.y][data_len] = height;
		map->min = height < map->min ? height : map->min;
		map->max = height > map->max ? height : map->max;
		data_len++;
	}
	map->heightmap[map->size.y][data_len] = INT_MIN;
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
		msg_exit("Empty file ?", 0);
	if (close(fd) == -1)
		msg_exit("Cannot close file", NULL);
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

t_map			*actually_read(t_map *map, int fd)
{
	char		**tab;
	int			len;
	char		*line;
	int			i;

	while ((i = get_next_line(fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = fill_map_line(tab, map);
		if (len > map->size.x)
			map->size.x = len;
		++map->size.y;
		free(line);
		ft_free_tab(&tab);
	}
	if (i == -1)
		msg_exit("Read error (malloc() or read() failed)", 0);
	if (map->min == 0 && map->max == 0)
		map->max = 1;
	map->median = (map->min + map->max) / 2.;
	map->delta = map->max - map->min;
	return (map);
}

t_map			*read_map(t_map *map, char *filename)
{
	int			fd;

	map->min = 0;
	map->max = 0;
	map->size.y = map_height(filename);
	if (!map->heightmap = malloc(map->size.y * sizeof(int*)))
		msg_exit("Not enought memory.", 0);
	if (!(fd = open(filename, O_RDONLY)))
		msg_exit("Cannot open file \"%s\"", filename);
	map->size.y = 0;
	return (actually_read(map, fd));
}

