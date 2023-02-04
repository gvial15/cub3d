#include "cub3d.h"

static int	skip_to_map(t_cub3d *cub3d)
{
	int		count;
	int		map_fd;
	char	*line;

	map_fd = open(cub3d->map_path, O_RDONLY);
	count = 0;
	while (count != 6)
	{
		line = get_next_line(map_fd);
		if (!line)
			break;
		if (line[0] == 'N' || line[0] == 'E' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'C' || line[0] == 'F')
			count++;
		free(line);
	}
	return (map_fd);
}


static char	*fill_map(t_cub3d *cub3d)
{
	char	*map;
	char	*line;
	int		map_fd;

	map = NULL;
	map_fd = skip_to_map(cub3d);
	line = get_next_line(map_fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	while (line && line[0] != '\n')
	{
		map = ft_strjoin_gnl(map, line);
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map);
}

static void	verify_map(t_cub3d *cub3d, char *map)
{
	int	i;

	i = -1;
	while (map[++i])
		if (map[i] != '1' && map[i] != '0' && map[i] != ' ' && map[i] != '\n'
			&& map[i] != 'N' && map[i] != 'S' && map[i] != 'W' && map[i] != 'E')
			map_error(cub3d, map);
}

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
			if ((y == 0 || y == cub3d->map.height - 1) && (map[y][x] != 1 && map[y][x] != -1))
				map_error(cub3d, map_c);
		}
		x = -1;
	}
}

static void	get_player(t_cub3d *cub3d, char *map)
{
	int	y;
	int	x;
	int	p;

	p = 0;
	x = -1;
	y = -1;
	while (++y < cub3d->map.height)
	{
		while (++x < cub3d->map.width)
		{
			if (cub3d->map.map[y][x] == 'N' - 48 || cub3d->map.map[y][x] == 'S' - 48 || cub3d->map.map[y][x] == 'E' - 48 || cub3d->map.map[y][x] == 'W' - 48)
			{
				if (p == 1)
					player_error(map);
				p = 1;
				cub3d->player.orientation = cub3d->map.map[y][x] + 48;
				cub3d->player.x = x;
				cub3d->player.y = y;
			}
		}
		x = -1;
	}
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
	// verify_walls(cub3d, cub3d->map.map, map);
	// get player's x and y position and orientation

	free(map);
}
