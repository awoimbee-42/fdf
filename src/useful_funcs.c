/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:47:40 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/08 22:19:27 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		exit(EXIT_FAILURE);
}

void	ft_exit(t_data *data)
{
	while (--data->map->size.y != -1)
	{
		free(data->zbuff[data->map->size.y]);
		free(data->map->heightmap[data->map->size.y]);
	}
	free(data->zbuff);
	free(data->map->heightmap);
	free(data->mlx);
	free(data->map);
	free(data);
	exit(EXIT_SUCCESS);
}
