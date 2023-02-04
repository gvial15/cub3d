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

static void	verify_walls(t_cub3d *cub3d, int height, int **map, char *map_c)
{
	int	x;
	int	y;

	y = -1;
	x = -1;
	while (map[++y][x])
	{
		while (map[y][++x])
		{
			if ( ((y == 0 || y == height - 1) && (map[y][x] != '1' || map[x][y] != ' ')) )
				map_error(cub3d, map_c);
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
	verify_walls(cub3d, cub3d->map.height, cub3d->map.map, map);
	// get player's x and y position and orientation
	// verify_player();
	free(map);
}
