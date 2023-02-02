#include "cub3d.h"
#include "lib/libft/libft.h"

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

static void	alloc_map(t_cub3d *cub3d, char *map)
{
	int		i;
	int		x;
	int		y;
	char	**split;

	split = ft_split(map, '\n');
	y = split_len(split);
	x = 0;
	i = -1;
	while (split[++i])
		if (ft_strlen(split[i]) > x)
			x = ft_strlen(split[i]);
	cub3d->map.map = malloc(sizeof(int *) * y);
	i = y;
	while (--i >= 0)
		cub3d->map.map[i] = ft_calloc(x, sizeof(int));
	cub3d->map.height = y;
	cub3d->map.width = x;
	free(split);
}

static void	log_map(t_cub3d *cub3d, char *map)
{
	int		i;
	int		x;
	int		z;
	char	**split;

	split = ft_split(map, '\n');
	i = -1;
	z = 0;
	x = -1;
	while (split[++i])
	{
		while (++x < cub3d->map.width)
		{
			if (split[i][z] && split[i][z] != ' ')
				cub3d->map.map[i][x] = split[i][z] - 48;
			else
				cub3d->map.map[i][x] = -1;
			z++;
		}
		x = -1;
		z = 0;
	}
}

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	char	*map;

	map = fill_map(cub3d);
	// verify_map(map); // verify if map is only 1 0 \n NSEW
	alloc_map(cub3d, map);
	log_map(cub3d, map);
	// verify_walls(cub3d->map.map);
	// get player's x and y position and orientation
	// verify_player();
	free(map);
}
