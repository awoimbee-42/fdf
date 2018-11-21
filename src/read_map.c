/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:30:46 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/21 15:15:21 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
int		map_realloc(t_map *map, size_t addsize)
{
	int			*nw_hmap;
	size_t		old_size;

	if (map->heightmap)
	{
		old_size = 0;
		while (map->heightmap[old_size] != INT_MIN)
			old_size += 1;
	}
	else
		old_size = 0;
	if (!(nw_hmap = ft_memalloc((old_size + addsize + 1) * sizeof(int))))
		return (0);
	if (old_size)
	{
		nw_hmap = ft_memcpy(nw_hmap, map->heightmap, old_size * sizeof(int));
		free(map->heightmap);
	}
	nw_hmap[old_size] = INT_MIN;
	map->heightmap = nw_hmap;
	return (1);
}
*/


/*
**	Returns nb of int read
*/
int		fill_map_line(char **data, size_t line_nb, t_map *map)
{
	char	**tmp;
	size_t	data_len;
	int		**heightmap;
	int		height;

	heightmap = map->heightmap;
	tmp = data;
	while (*tmp)
		++tmp;
	if (!(heightmap[line_nb] = malloc((tmp - data + 1) * sizeof(int))))
		msg_exit("cannot malloc heightmap line !", 0);
	data_len = 0;
	while (data[data_len])
	{
		height = ft_atoi(data[data_len]);
		heightmap[line_nb][data_len] = height;
		if (height < map->z_min)
			map->z_min = height;
		else if (height > map->z_max)
			map->z_max = height;
		data_len++;
	}
	heightmap[line_nb][data_len] = INT_MIN;
	return (data_len);
}

static	size_t map_height(char *filename)
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

t_map	*read_map(t_map *map, char *filename)
{
	char	*line;
	char	**tab;
	int		fd;
	size_t	line_nb;
	int		len;

	map->size.y = map_height(filename);
	map->heightmap = malloc(map->size.y * sizeof(int*));
	line_nb = 0;
	if (!(fd = open(filename, O_RDONLY)))
		msg_exit("Cannot open file \"%s\"", filename);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = fill_map_line(tab, line_nb, map);
		if (len > map->size.x)
			map->size.x = len;
		++line_nb;
		free(line);
	}
	return (map);
}
