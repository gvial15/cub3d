/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:31:41 by gvial             #+#    #+#             */
/*   Updated: 2023/04/17 13:55:58 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error(t_cub3d *cub3d, char **split_space, char *line)
{
	free(line);
	close(cub3d->map_fd);
	free_split((void **)split_space, split_len((void **)split_space));
	color_error(NULL);
}

int	get_index(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isalpha(line[i]))
		i++;
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
static void	fill_color(char *line, int color[3])
{
	int		i;
	int		ii;
	char	**split;

	split = ft_split(line, ',');
	if (split_len((void **)split) != 3)
		color_error(split);
	i = -1;
	ii = -1;
	while (split[++i])
	{
		while (split[i][++ii])
			if (ft_strlen(split[i]) < 1 || split[i][0] == '\n' ||\
				(!ft_isdigit(split[i][ii]) && split[i][ii] != '\n'\
				&& split[i][ii + 1] != '\0'))
				color_error(split);
		ii = -1;
	}
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	free_split((void **)split, split_len((void **)split));
}

// parse ceilling and floor color into cub3d->map.<f/c>_color[3];
void	get_colors(t_cub3d *cub3d)
{
	char	*line;
	char	**split_space;

	split_space = NULL;
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
		if ((split_len((void **)split_space) != 2 \
			&& (line[get_index(line)] == 'C' || line[get_index(line)] == 'F')))
			error(cub3d, split_space, line);
		if (line[get_index(line)] == 'C')
			fill_color(split_space[1], cub3d->map.c_color);
		if (line[get_index(line)] == 'F')
			fill_color(split_space[1], cub3d->map.f_color);
		free_split((void **)split_space, split_len((void **)split_space));
		free(line);
	}
	close(cub3d->map_fd);
}
