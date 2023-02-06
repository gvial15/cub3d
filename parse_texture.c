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

static char	*get_file_path(char *line)
{
	char	*file_path;

	if (!line)
		return (NULL);
	file_path = ft_substr(line, 3, ft_strlen(line) - 4);
	return (file_path);
}

static void	get_img(t_cub3d *cub3d, char *file_path, char *line)
{
	if (ft_strnstr(line, "NO ", 3))
		cub3d->display.n_texture = mlx_xpm_file_to_image(cub3d->display.mlx, \
		file_path, &cub3d->display.img_width, &cub3d->display.img_height);
	else if (ft_strnstr(line, "SO ", 3))
		cub3d->display.s_texture = mlx_xpm_file_to_image(cub3d->display.mlx, \
		file_path, &cub3d->display.img_width, &cub3d->display.img_height);
	else if (ft_strnstr(line, "WE ", 3))
		cub3d->display.w_texture = mlx_xpm_file_to_image(cub3d->display.mlx, \
		file_path, &cub3d->display.img_width, &cub3d->display.img_height);
	else if (ft_strnstr(line, "EA ", 3))
		cub3d->display.e_texture = mlx_xpm_file_to_image(cub3d->display.mlx, \
		file_path, &cub3d->display.img_width, &cub3d->display.img_height);
}

// parse textures and store images pointer to cub3d->display.<n/s/e/w>_texture
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
		get_img(cub3d, file_path, line);
		free(line);
		free(file_path);
	}
	close(cub3d->map_fd);
	if (!cub3d->display.e_texture || !cub3d->display.s_texture
		|| !cub3d->display.w_texture || !cub3d->display.n_texture)
		texture_error();
}
