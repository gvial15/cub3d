/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:31:41 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:31:42 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error(t_cub3d *cub3d, char **split_space, char *line)
{
	free(line);
	close(cub3d->map_fd);
	free_split((void **)split_space, split_len((void **)split_space));
	color_error();
}

int	get_index(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && !ft_isalpha(line[i]));
	return (i);
}

// verify if ceiling and floor colors are specified in the .cub file
static int	f_c(t_cub3d *cub3d)
{
	char	*line;
	int		f;
	int		c;

	cub3d->map_fd = open(cub3d->map_path, O_RDONLY);
	f = 0;
	c = 0;
	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		if (!line)
			break ;
		if (line[get_index(line)] == 'C')
			c++;
		if (line[get_index(line)] == 'F')
			f++;
		free(line);
	}
	free(line);
	close(cub3d->map_fd);
	if (f != 1 || c != 1)
		return (0);
	return (1);
}

// fill the int[3] with the rgb values
static void	fill_color(char *line, int color[3], t_cub3d *cub3d)
{
	char	**split_comma;

	split_comma = ft_split(line, ',');
	if (split_len((void **)split_comma) != 3)
	{
		free(split_comma);
		color_error();
	}
	color[0] = ft_atoi(split_comma[0]);
	color[1] = ft_atoi(split_comma[1]);
	color[2] = ft_atoi(split_comma[2]);
	free_split((void **)split_comma, split_len((void **)split_comma));
}

// parse ceilling and floor color into cub3d->map.<f/c>_color[3];
void	get_colors(t_cub3d *cub3d)
{
	char	*line;
	char	**split_space;

	line = NULL;
	if (!f_c(cub3d))
		error(cub3d, split_space, line);
	cub3d->map_fd = open(cub3d->map_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		if (!line)
			break ;
		split_space = ft_split(line, ' ');
		if ((split_len((void **)split_space) != 2 && (line[get_index(line)] == 'C' || line[get_index(line)] == 'F')))
			error(cub3d, split_space, line);
		if (line[get_index(line)] == 'C')
			fill_color(split_space[1], cub3d->map.c_color, cub3d);
		if (line[get_index(line)] == 'F')
			fill_color(split_space[1], cub3d->map.f_color, cub3d);
		free_split((void **)split_space, split_len((void **)split_space));
		free(line);
	}
	close(cub3d->map_fd);
}
