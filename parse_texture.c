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

// parse the file path
static char	*get_file_path(char *line)
{
	char	*file_path;

	if (!line)
		return (NULL);
	file_path = ft_substr(line, 3, ft_strlen(line) - 4);
	return (file_path);
}

// alloc the char* to char** cub3d->texture[i].texture
static void	alloc_texture(t_cub3d *cub3d, char *line, int index)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[++i]));
	line[i] = 0;
	cub3d->textures[index].texture = ft_calloc(ft_atoi(&line[i + 1]) + 1, sizeof(char *));
}

// parse the texture into char** cub3d->texture[i].texture
static void	get_texture(t_cub3d *cub3d, int index, char *file_path)
{
	char	*line;
	int		i;
	int	fd;

	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	while (!ft_strnstr(line, "/* pixels */", 12))
	{
		if (line[0] == '"' && ft_isdigit(line[1]))
			alloc_texture(cub3d, line, index);
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	i = -1;
	while (!ft_strnstr(line, "};", 12))
	{
		cub3d->textures[index].texture[++i] = ft_strtrim(line, "\",\n");
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

// find the orientation of the texture to parse it into the right t_texture index
static void	parse_xpm(t_cub3d *cub3d, char *file_path, char *line)
{
	if (ft_strnstr(line, "NO ", 3))
	{
		get_texture(cub3d, 0, file_path);
		get_texture_colors(cub3d, 0, file_path);
	}
	else if (ft_strnstr(line, "SO ", 3))
	{
		get_texture(cub3d, 1, file_path);
		get_texture_colors(cub3d, 1, file_path);
	}
	else if (ft_strnstr(line, "WE ", 3))
	{
		get_texture(cub3d, 2, file_path);
		get_texture_colors(cub3d, 2, file_path);
	}
	else if (ft_strnstr(line, "EA ", 3))
	{
		get_texture(cub3d, 3, file_path);
		get_texture_colors(cub3d, 3, file_path);
	}
}

// parse textures in char** and color in map {character: color}
void	parse_texture(t_cub3d *cub3d)
{
	char	*line;
	char	*file_path;

	cub3d->map_fd = open(cub3d->map_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		file_path = get_file_path(line);
		if (!line)
			break ;
		parse_xpm(cub3d, file_path, line);
		free(line);
		free(file_path);
	}
	// print_split(cub3d->textures[0].texture);
	// print_split(cub3d->textures[0].colors);
	// printf("\n\n");
	// print_split(cub3d->textures[1].texture);
	// print_split(cub3d->textures[1].colors);
	// printf("\n\n");
	// print_split(cub3d->textures[2].texture);
	// print_split(cub3d->textures[2].colors);
	// printf("\n\n");
	// print_split(cub3d->textures[3].texture);
	// print_split(cub3d->textures[3].colors);
	close(cub3d->map_fd);
}
