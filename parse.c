/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:30:08 by gvial             #+#    #+#             */
/*   Updated: 2023/03/22 14:13:26 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cub3d *cub3d)
{
	free_split((void **)cub3d->map.map, split_len((void **)cub3d->map.map_d));
	free_split((void **)cub3d->map.map_d, split_len((void **)cub3d->map.map_d));
}

void	free_textures(t_cub3d *cub3d)
{
	int	i;
	int	len;

	i = -1;
	while (++i < 4)
	{
		len = split_len((void **)cub3d->textures[i].texture);
		free_split((void **)cub3d->textures[i].texture, len);
	}
	i = -1;
	while (++i < 4)
		free(cub3d->textures[i].colors);
}

// verify argument end in .cub
static void	parse_arg(char *map_path)
{
	int	i;
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		arg_error();
	i = ft_strlen(map_path);
	while (map_path[--i])
	{
		if (i == (int)ft_strlen(map_path) - 1 && map_path[i] != 'b')
			arg_error();
		if (i == (int)ft_strlen(map_path) - 2 && map_path[i] != 'u')
			arg_error();
		if (i == (int)ft_strlen(map_path) - 3 && map_path[i] != 'c')
			arg_error();
		if (i == (int)ft_strlen(map_path) - 4 && map_path[i] != '.')
			arg_error();
	}
}

void	set_orientation(t_cub3d *cub3d, char c)
{
	if (c == 2)
		cub3d->player.degrees = 0.0f;
	else if (c == 3)
		cub3d->player.degrees = 90.0f;
	else if (c == 4)
		cub3d->player.degrees = 180.0f;
	else if (c == 5)
		cub3d->player.degrees = 270.0f;
}

void	parse(t_cub3d *cub3d)
{
	parse_arg(cub3d->map_path);
	get_colors(cub3d);
	parse_map(cub3d);
	parse_texture(cub3d);
}
