/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:30:08 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:30:09 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_arg(t_cub3d *cub3d, char *map_path)
{
	int		i;

	i = ft_strlen(map_path);
	while (map_path[--i])
	{
		if (i == ft_strlen(map_path) - 1 && map_path[i] != 'b')
			arg_error();
		if (i == ft_strlen(map_path) - 2 && map_path[i] != 'u')
			arg_error();
		if (i == ft_strlen(map_path) - 3 && map_path[i] != 'c')
			arg_error();
		if (i == ft_strlen(map_path) - 4 && map_path[i] != '.')
			arg_error();
	}
}

void	parse(t_cub3d *cub3d)
{
	parse_arg(cub3d, cub3d->map_path);
	parse_texture(cub3d);
	get_colors(cub3d);
	parse_map(cub3d);
}
