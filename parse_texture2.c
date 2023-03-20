/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:35:17 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:35:18 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	nb_color(char *file_path)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	while (line[0] != '"' && !ft_isdigit(line[1]))
	{
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (!ft_strnstr(line, "/* pixels */", 12))
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

void	parse_color(t_cub3d *cub3d, char *line, int index)
{
	char **split = ft_split(line, ' ');
	// print_split(split);
	// "char c color"
	// ". c #3E2731"
	free_split((void **)split, split_len(split));
}

void	get_texture_colors(t_cub3d *cub3d, int index, char *file_path)
{
	int		fd;
	char	*line;

	// nb_color() makes get_next_line() not begin by the start of file here after it returns
	cub3d->textures[index].colors = ft_calloc((nb_color(file_path) * 2) + 1, sizeof(char *));
	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	while (line[0] != '"' && !ft_isdigit(line[1]))
	{
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (!ft_strnstr(line, "/* pixels */", 12))
	{
		parse_color(cub3d, line, index);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}
