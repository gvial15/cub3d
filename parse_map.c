#include "cub3d.h"
#include "lib/libft/get_next_line/get_next_line.h"

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

static void	verify_walls(char *map) // might have to verify once the map is in a int**
{									// because i cant verify if empty spaces in
	int	i;							// middle of map are surrounded by walls

	if (map[0] != '1' && map[0] != ' ')
		map_error(map);
	i = 0;
	while (map[++i])
	{
		if (map[i] != '1' && map[i] != ' ' && map[i] != '0' && map[i] != 'N'
			&& map[i] != 'E' && map[i] != 'S' && map[i] != 'W' && map[i] != '\n')
			map_error(map);
		if (map[i - 1] == '\n' && map[i] != '1')
			map_error(map);
		if (map[i - 1] == ' ' && map[i] != '1')
			map_error(map);
		if (map[i + 1] == '\n' && map[i] != '1')
			map_error(map);
		if (map[i + 1] == ' ' && map[i] != '1')
			map_error(map);
	}
}

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	char	*map;

	map = fill_map(cub3d);
	verify_walls(map);
	// log map into a int**
	// log_map(cub3d->map.map);
	// verify map has walls all around it
	// get player's x and y position and orientation

	free(map);
}
