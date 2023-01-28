#include "cub3d.h"

static char	*get_file_path(char *line)
{
	char	*file_path;

	if (!line)
		return (NULL);
	file_path = ft_substr(line, 3, ft_strlen(line) - 4);
	return (file_path);
}

// parsing the texture in the .cub file and storing the img pointer to cub3d->display.<n/s/e/w>_texture
void	parse_texture(t_cub3d *cub3d)
{
	char	*line;
	char	*file_path;

	while(1)
	{
		line = get_next_line(cub3d->map_fd);
		file_path = get_file_path(line);
		if (!line)
			break;
		if (ft_strnstr(line, "NO ", 3))
			cub3d->display.n_texture = mlx_xpm_file_to_image(cub3d->display.mlx,\
			file_path, &cub3d->display.img_width, &cub3d->display.img_height);
		else if (ft_strnstr(line, "SO ", 3))
			cub3d->display.s_texture = mlx_xpm_file_to_image(cub3d->display.mlx,\
			file_path, &cub3d->display.img_width, &cub3d->display.img_height);
		else if (ft_strnstr(line, "WE ", 3))
			cub3d->display.w_texture = mlx_xpm_file_to_image(cub3d->display.mlx,\
			file_path, &cub3d->display.img_width, &cub3d->display.img_height);
		else if (ft_strnstr(line, "EA ", 3))
			cub3d->display.e_texture = mlx_xpm_file_to_image(cub3d->display.mlx,\
			file_path, &cub3d->display.img_width, &cub3d->display.img_height);
		free(line);
		free(file_path);
	}
	if (!cub3d->display.e_texture || !cub3d->display.s_texture || !cub3d->display.w_texture
		|| !cub3d->display.n_texture)
		texture_error(cub3d);
}