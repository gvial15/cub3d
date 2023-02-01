#include "cub3d.h"

// put map file into a char* in case its needed (idk)
void	get_map(t_cub3d *cub3d)
{
	char	*line;

	cub3d->map_fd = open(cub3d->map_path, O_RDONLY);
	line = get_next_line(cub3d->map_fd);
	while (line)
	{
		cub3d->map.map_c = ft_strjoin_gnl(cub3d->map.map_c, line);
		free(line);
		line = get_next_line(cub3d->map_fd);
	}
	close(cub3d->map_fd);
}

void	parse(t_cub3d *cub3d)
{
	get_map(cub3d);

	parse_texture(cub3d);
	get_colors(cub3d);
	parse_map(cub3d);
}
