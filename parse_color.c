#include "cub3d.h"

static int	f_c(int	map_fd)
{
	char	*line;
	int		f;
	int		c;

	f = 0;
	c = 0;
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break;
		if (line[0] == 'C')
			c++;
		if (line[0] == 'F')
			f++;
	}
	if (f == 0 || c == 0)
		return (0);
	return (1);
}

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

// parse ceilling and floor color into cub3d->map.<f/c>_color[3];
void	get_colors(t_cub3d *cub3d)
{
	char	*line;
	char	**split_space;

	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		if (!line)
			break;
		split_space = ft_split(line, ' ');
		if ((!f_c(cub3d->map_fd)) || (split_len(split_space) != 2 && (line[0] == 'C' || line[0] == 'F')))
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
