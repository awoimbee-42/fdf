/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:30:46 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 18:12:19 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		map_realloc(t_map *map, size_t addsize)
{
	t_vertex	*nw_verts;
	size_t		old_size;

	if (map->verts)
	{
		old_size = 0;
		while (map->verts[old_size].x != __FLT_MAX__)
			old_size += 1;
	}
	else
		old_size = 0;
	if (!(nw_verts = ft_memalloc((old_size + addsize + 1) * sizeof(t_vertex))))
		return (0);
	if (old_size)
	{
		nw_verts = ft_memcpy(nw_verts, map->verts, old_size * sizeof(t_vertex));
		free(map->verts);
	}
	nw_verts[old_size].x = __FLT_MAX__;
	map->verts = nw_verts;
	return (1);
}

void	fill_map_line(char **data, size_t line_nb, t_map *map)
{
	char	**tmp;
	size_t	map_s;
	size_t	data_s;
	int		tmp_int;

	tmp = data;
	while (*tmp)
		++tmp;
	map_realloc(map, (tmp - data)); //NEED ERR CHECK
	map_s = 0;
	while (map->verts[map_s].x != __FLT_MAX__)
		map_s += 1;
	data_s = 0;
	while (data[data_s])
	{
		map->verts[map_s].x = data_s;
		map->verts[map_s].y = line_nb;
		map->verts[map_s].z = ft_atoi(data[data_s]);
		map_s++;
		data_s++;
	}
	map->verts[map_s].x = __FLT_MAX__;
}

t_map	*read_map(t_map *map, char *filename)
{
	char	*line;
	char	**tab;
	int		fd;
	size_t	line_nb;

	if (!(fd = open(filename, O_RDONLY)))
		msg_exit("Cannot open file \"%s\"", filename);
	line_nb = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		fill_map_line(tab, line_nb, map);
		++line_nb;
	}


	return (map);
}
