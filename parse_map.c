/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:33:52 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:33:54 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verify_walls(t_cub3d *cub3d, int **map, char *map_c)
{

}

static int	parse_player_norm(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map.map[y][x] == 2 || cub3d->map.map[y][x] == 3
		|| cub3d->map.map[y][x] == 4 || cub3d->map.map[y][x] == 5)
		return (1);
	return (0);
}

// find player coordinate and orientation
static void	parse_player(t_cub3d *cub3d, char *map)
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

void	verify_map(t_cub3d *cub3d, char *map)
{
	int	i;

	i = -1;
	while (map[++i])
		if (map[i] != '1' && map[i] != '0' && map[i] != ' ' && map[i] != '\n'
			&& map[i] != 'N' && map[i] != 'S' && map[i] != 'W' && map[i] != 'E')
			map_error(cub3d, map);
}

// parse the map into cub3d->map.map and player x/y and orientation..
// could put it in parse.c if i need more space here.
void	parse_map(t_cub3d *cub3d)
{
	char	*map;

	map = fill_map(cub3d);
	verify_map(cub3d, map);
	alloc_map(cub3d, map);
	log_map(cub3d, map);
	parse_player(cub3d, map);
	verify_walls(cub3d, cub3d->map.map, map);
	free(map);
}
