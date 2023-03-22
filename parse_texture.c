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

static char	**alloc_file(char *file_path)
{
	char	**file;
	char	*line;
	int		fd;
	int		i;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	file = ft_calloc(i + 1, sizeof(char *));
	return (file);
}

// parse texture file into a char ** so i don't have to use gnl each time i want to read it after
static char	**parse_file(char *file_path)
{
	int		i;
	int		fd;
	char	*line;
	char	**file;

	file = alloc_file(file_path);
	if (!file)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	i = 0;
	file[i] = get_next_line(fd);
	while (file[i++])
		file[i] = get_next_line(fd);
	close(fd);
	return (file);
}

// parse the texture into char** cub3d->texture[i].texture
static void	get_texture(t_cub3d *cub3d, int index, char **file)
{
	int		i;
	int		ii;

	i = -1;
	ii = -1;
	while (!ft_strnstr(file[++i], "/* pixels */", 12))
	{
		if (file[i][0] == '"' && ft_isdigit(file[i][1]))
		{
			while (ft_isdigit(file[i][++ii]));
			file[i][ii] = 0;
			cub3d->textures[index].texture = ft_calloc(ft_atoi(&file[i][ii + 1]) + 1, sizeof(char *));
		};
	}
	ii = -1;
	while (!ft_strnstr(file[++i], "};", 12))
		cub3d->textures[index].texture[++ii] = ft_strtrim(file[i], "\",\n");
}

// find the orientation of the texture to parse it into the right t_texture index
static void	parse_xpm(t_cub3d *cub3d, char **file, char *line)
{
	if (ft_strnstr(line, "NO ", 3))
	{
		get_texture(cub3d, 0, file);
		get_texture_colors(cub3d, 0, file);
	}
	else if (ft_strnstr(line, "SO ", 3))
	{
		get_texture(cub3d, 1, file);
		get_texture_colors(cub3d, 1, file);
	}
	else if (ft_strnstr(line, "WE ", 3))
	{
		get_texture(cub3d, 2, file);
		get_texture_colors(cub3d, 2, file);
	}
	else if (ft_strnstr(line, "EA ", 3))
	{
		get_texture(cub3d, 3, file);
		get_texture_colors(cub3d, 3, file);
	}
}

// parse textures in char** and color in map {character: color}
void	parse_texture(t_cub3d *cub3d)
{
	char	*line;
	char	**file;
	char	*file_path;

	cub3d->map_fd = open(cub3d->map_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(cub3d->map_fd);
		if (!line)
			break ;
		file_path = ft_substr(line, 3, ft_strlen(line) - 4);
		file = parse_file(file_path);
		parse_xpm(cub3d, file, line);
		free(line);
		free(file_path);
		free_split((void **)file, split_len(file));
	}
	// print_split(cub3d->textures[0].texture);
	// print_int_tab(cub3d->textures[0].colors, 10);
	// printf("\n\n");
	// print_split(cub3d->textures[1].texture);
	// print_int_tab(cub3d->textures[1].colors, 10);
	// printf("\n\n");
	// print_split(cub3d->textures[2].texture);
	// print_int_tab(cub3d->textures[2].colors, 10);
	// printf("\n\n");
	// print_split(cub3d->textures[3].texture);
	// print_int_tab(cub3d->textures[3].colors, 10);
	close(cub3d->map_fd);
}
