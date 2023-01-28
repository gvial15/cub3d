#include "cub3d.h"

static void	fill_color(char *line, int	color[3], t_cub3d *cub3d)
{
	char	**split_comma;

	split_comma = ft_split(line, ',');
	if (split_len(split_comma) != 3)
	{
		free(split_comma);
		color_error(cub3d);
	}
	color[0] = ft_atoi(split_comma[0]);
	color[1] = ft_atoi(split_comma[1]);
	color[2] = ft_atoi(split_comma[2]);
	free(split_comma);
}

static void	get_colors(t_cub3d *cub3d)
{
	char	*line;
	char	**split_space;

	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		if (!line)
			break;
		split_space = ft_split(line, ' ');
		if (split_len(split_space) != 2 && (line[0] == 'C' || line[0] == 'F'))
		{
			free_split(split_space);
			color_error(cub3d);
		}
		if (line[0] == 'C')
			fill_color(split_space[1], cub3d->map.c_color, cub3d);
		if (line[0] == 'F')
			fill_color(split_space[1], cub3d->map.f_color, cub3d);
		free_split(split_space);
	}
}

t_cub3d	*parse(char *arg)
{
	t_cub3d	*cub3d;

	if (!arg)
		arg_error(cub3d);
	cub3d = malloc(sizeof(t_cub3d));
	cub3d->map_fd = open(arg, O_RDONLY);

	// mlx_xpm_file_to_image(); segfault
	// parse_texture(cub3d);

	// todo: parse ceilling and floor color into cub3d->map.<f/c>_color[3];
	get_colors(cub3d);

	// todo: parse the map into an int**

	close(cub3d->map_fd);
	return (cub3d);
}
