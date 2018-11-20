/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:30:46 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/20 17:30:58 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*map_realloc(int *old_tab, size_t addsize)
{
	int			*nw_tab;
	size_t		old_size;

	if (old_tab)
	{
		old_size = 0;
		while (old_tab[old_size] != 0xFFFF)
			old_size += 3;
	}
	else
		old_size = 0;
	if (!(nw_tab = ft_memalloc((old_size + addsize) * sizeof(int))))
		return (NULL);
	if (old_size)
	{
		nw_tab = ft_memcpy(nw_tab, old_tab, old_size * sizeof(int));
		free(old_tab);
	}
	return (nw_tab);
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
	map->coords = map_realloc(map->coords, (tmp - data) * 3 + 1);
	map_s = 0;
	while (map->coords[map_s] != 0xFFFF)
		map_s += 3;
	data_s = 0;
	while (data[data_s])
	{
		tmp_int = data_s;
		ft_memcpy(&(map->coords[map_s++]), &tmp_int, sizeof(int));
		tmp_int = line_nb;
		ft_memcpy(&(map->coords[map_s++]), &tmp_int, sizeof(int));
		tmp_int = ft_atoi(data[data_s]);
		ft_memcpy(&(map->coords[map_s++]), &tmp_int, sizeof(int));
		data_s++;
	}
	map->coords[map_s] = 0xFFFF;
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

	map = malloc(sizeof(t_map));
	map->coords = malloc(sizeof(int) * 3 * 10 + sizeof(int));


	return (map);
}
