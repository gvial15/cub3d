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
	}
	return (map_fd);
}

static void	alloc_map(t_cub3d *cub3d)
{
	char	*line;
	int		map_fd;
	int		x;
	int		y;

	map_fd = skip_to_map(cub3d);
	y = 0;
	x = 0;
	line = get_next_line(map_fd);
	while (line[0] == '\n')
		line = get_next_line(map_fd);
	while (line && line[0] != '\n')
	{
		y++;
		if (ft_strlen_gnl(line) - 1 > x)
			x = ft_strlen_gnl(line) - 1;
		line = get_next_line(map_fd);
	}
	cub3d->map.map = ft_calloc(y, sizeof(int*));
	cub3d->map.height = y;
	cub3d->map.width = x;
	while (y >= 0)
		cub3d->map.map[y--] = ft_calloc(x, sizeof(int));
	close(map_fd);
}

static void	fill_map(t_cub3d *cub3d, char *line, int y)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n') //  change this to 1 || 0 || ...
		cub3d->map.map[y][i] = line[i] - 48;
	if (i < cub3d->map.width)
		while (i < cub3d->map.width)
			cub3d->map.map[y][i++] = 2;
}

static void	log_map(t_cub3d *cub3d)
{
	char	*line;
	int		map_fd;
	int		y;

	y = 0;
	map_fd = skip_to_map(cub3d);
	line = get_next_line(map_fd);
	while (line[0] == '\n')
		line = get_next_line(map_fd);
	while (line && line[0] != '\n')
	{
		fill_map(cub3d, line, y);
		line = get_next_line(map_fd);
		y++;
	}
}

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	alloc_map(cub3d);
	log_map(cub3d);
	// verify map has walls all around it
	// get player's x and y position and orientation
}
