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
#include "lib/libft/libft.h"

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

// convert characters into int (colors) and put it into the given cub3d->textures[index].texture[++ii]
int	*get_texture_color(t_texture *texture, char *line)
{
	int		i;
	int		ii;
	int		*tab;
	char	*new_line;

	new_line = ft_strtrim(line, "\",\n");
	tab = ft_calloc(ft_strlen(new_line) + 1, sizeof(int));
	i = -1;
	ii = 0;
	while (new_line[++i])
	{
		while (texture->colors[ii++] != new_line[i]);
		tab[i] = texture->colors[ii];
		ii = 0;
	}
	free(new_line);
	return (tab);
}

// parse the texture into int** cub3d->texture[i].texture
static void	get_texture(t_cub3d *cub3d, int index, char **file, char *line)
{
	int		i;
	int		ii;

	i = -1;
	ii = -1;
	if (!file)
		texture_error(line, file);
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
		cub3d->textures[index].texture[++ii] = get_texture_color(&cub3d->textures[index], file[i]);
}

// find the orientation of the texture to parse it into the right t_texture index
static void	parse_xpm(t_cub3d *cub3d, char **file, char *line)
{
	if (ft_strnstr(line, "NO ", 3))
	{
		get_texture_colors(cub3d, 0, file);
		get_texture(cub3d, 0, file, line);
	}
	else if (ft_strnstr(line, "SO ", 3))
	{
		get_texture_colors(cub3d, 1, file);
		get_texture(cub3d, 1, file, line);
	}
	else if (ft_strnstr(line, "WE ", 3))
	{
		get_texture_colors(cub3d, 2, file);
		get_texture(cub3d, 2, file, line);
	}
	else if (ft_strnstr(line, "EA ", 3))
	{
		get_texture_colors(cub3d, 3, file);
		get_texture(cub3d, 3, file, line);
	}
}

// testing...
// void	print_int_tab2(int *tab, int size)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < size)
// 	{
// 		ft_printf("%i", tab[i]);
// 		ft_printf(" ");
// 	}
// 	ft_printf("\n");
// }

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
		free(file_path);
		parse_xpm(cub3d, file, line);
		free(line);
		free_split((void **)file, split_len((void **)file));
	}
	// testing...
	// int	i;
	// i = -1;
	// while (++i < 16)
	// 	print_int_tab2(cub3d->textures[0].texture[i], 16);
	// print_int_tab(cub3d->textures[0].colors, 10);
	// printf("\n\n");
	// i = -1;
	// while (++i < 16)
	// 	print_int_tab2(cub3d->textures[1].texture[i], 16);
	// print_int_tab(cub3d->textures[1].colors, 10);
	// printf("\n\n");
	// i = -1;
	// while (++i < 16)
	// 	print_int_tab2(cub3d->textures[2].texture[i], 16);
	// print_int_tab(cub3d->textures[2].colors, 10);
	// printf("\n\n");
	// i = -1;
	// while (++i < 16)
	// 	print_int_tab2(cub3d->textures[3].texture[i], 16);
	// print_int_tab(cub3d->textures[3].colors, 10);
	close(cub3d->map_fd);
}
