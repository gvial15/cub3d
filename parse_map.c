/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marie-soleiljarry <marie-soleiljarry@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:52 by gvial             #+#    #+#             */
/*   Updated: 2023/02/22 14:37:01 by marie-solei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// flood fill to verify the map is closed by walls
static void	verify_walls(t_cub3d *cub3d, int x, int y)
{
	if (y >= cub3d->map.height || x >= ft_strlen(cub3d->map.map_d[y])
		|| cub3d->map.map_d[y][x] == ' ')
		map_error(cub3d);
	if (cub3d->map.map_d[y][x] == '0')
	{
		cub3d->map.map_d[y][x] = '=';
		verify_walls(cub3d, x + 1, y);
		verify_walls(cub3d, x - 1, y);
		verify_walls(cub3d, x, y + 1);
		verify_walls(cub3d, x, y - 1);
	}
}

static int	parse_player_norm(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map.map[y][x] == 2 || cub3d->map.map[y][x] == 3
		|| cub3d->map.map[y][x] == 4 || cub3d->map.map[y][x] == 5)
		return (1);
	return (0);
}

// find player coordinate and orientation
static void	parse_player(t_cub3d *cub3d)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	while (++y < cub3d->map.height)
	{
		while (++x < cub3d->map.width)
		{
			if (parse_player_norm(cub3d, x, y))
			{
				if (cub3d->norm_bs == 1)
					player_error(cub3d);
				cub3d->norm_bs = 1;
				cub3d->player.orientation = cub3d->map.map[y][x];
				set_orientation(cub3d, cub3d->player.orientation);
				cub3d->player.x = x;
				cub3d->player.y = y;
			}
		}
		x = -1;
	}
	if (cub3d->norm_bs != 1)
		player_error(cub3d);
}

// verify if map is only composed of allowed characters
static void	verify_map(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (cub3d->map.map_c[++i])
		if (cub3d->map.map_c[i] != '1' && cub3d->map.map_c[i] != '0'
			&& cub3d->map.map_c[i] != ' ' && cub3d->map.map_c[i] != '\n'
			&& cub3d->map.map_c[i] != 'N' && cub3d->map.map_c[i] != 'S'
			&& cub3d->map.map_c[i] != 'W' && cub3d->map.map_c[i] != 'E')
			map_error(cub3d);
}

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	cub3d->map.map_c = fill_map(cub3d);
	cub3d->map.map_d = ft_split(cub3d->map.map_c, '\n');
	verify_map(cub3d);
	alloc_map(cub3d);
	log_map(cub3d);
	parse_player(cub3d);
	cub3d->player.cx = (cub3d->player.x * PIXELS) + cub3d->player.dx;
	cub3d->player.cy = (cub3d->player.y * PIXELS) + cub3d->player.dy;
	cub3d->map.map_d[cub3d->player.y][cub3d->player.x] = '0';
	verify_walls(cub3d, cub3d->player.x, cub3d->player.y);
	free(cub3d->map.map_c);
	free_split((void **)cub3d->map.map_d, split_len(cub3d->map.map_d));
}
