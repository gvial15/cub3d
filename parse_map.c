/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marie-soleiljarry <marie-soleiljarry@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:52 by gvial             #+#    #+#             */
/*   Updated: 2023/02/09 18:20:12 by marie-solei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verify_walls(t_cub3d *cub3d, int **map, char *map_c)
{
	int	x;
	int	y;

	y = -1;
	x = -1;
	while (++y < cub3d->map.height)
	{
		while (++x < cub3d->map.width)
		{
			if ((y == 0 || y == cub3d->map.height - 1) && (map[y][x] != 1
				&& map[y][x] != -1))
				map_error(cub3d, map_c);
		}
		x = -1;
	}
}

static int	get_player_norm(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map.map[y][x] == 'N' - 48 || cub3d->map.map[y][x] == 'S' - 48
		|| cub3d->map.map[y][x] == 'E' - 48 || cub3d->map.map[y][x] == 'W' - 48)
		return (1);
	return (0);
}

static void	get_player(t_cub3d *cub3d, char *map)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	while (++y < cub3d->map.height)
	{
		while (++x < cub3d->map.width)
		{
			if (get_player_norm(cub3d, x, y))
			{
				if (cub3d->norm_bs == 1)
					player_error(map);
				cub3d->norm_bs = 1;
				cub3d->player.orientation = cub3d->map.map[y][x] + 48;
				cub3d->player.x = x;
				cub3d->player.y = y;
			}
		}
		x = -1;
	}
	if (cub3d->norm_bs != 1)
		player_error(map);
}

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	char	*map;

	map = fill_map(cub3d);
	verify_map(cub3d, map);
	alloc_map(cub3d, map);
	log_map(cub3d, map);
	get_player(cub3d, map);
	cub3d->player.cx = (cub3d->player.x * PIXELS) + cub3d->player.dx;
	cub3d->player.cy = (cub3d->player.y * PIXELS) + cub3d->player.dy;
	//cx & cy are the exacy positions of the player in pixels, not in coordinates
	// verify_walls(cub3d, cub3d->map.map, map);
	free(map);
}
