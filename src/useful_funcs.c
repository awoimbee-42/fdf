/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:47:40 by awoimbee          #+#    #+#             */
/*   Updated: 2019/06/18 23:30:38 by awoimbee         ###   ########.fr       */
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
	while (--data->map.size.y != (typeof(data->map.size.y))-1)
	{
		free(data->zbuff[data->map.size.y]);
		free(data->map.heightmap[data->map.size.y]);
	}
	free(data->zbuff);
	free(data->map.heightmap);
	free(data);
	exit(EXIT_SUCCESS);
}
