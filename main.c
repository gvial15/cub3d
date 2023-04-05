/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:29:39 by gvial             #+#    #+#             */
/*   Updated: 2023/03/27 17:18:28 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// might not be necessary will see at the end
static void	init(t_cub3d *cub3d, char *map_path)
{
	cub3d->map_path = map_path;
	cub3d->norm_bs = 0;
	cub3d->map_fd = 0;
	cub3d->map.c_color[0] = 0;
	cub3d->map.c_color[1] = 0;
	cub3d->map.c_color[2] = 0;
	cub3d->map.f_color[0] = 0;
	cub3d->map.f_color[1] = 0;
	cub3d->map.f_color[2] = 0;
	cub3d->map.map = NULL;
	cub3d->map.map_c = NULL;
	cub3d->map.height = 0;
	cub3d->map.width = 0;
	cub3d->display.mlx = mlx_init();
	cub3d->display.mlx_win = NULL;
	cub3d->display.img_width = 0;
	cub3d->display.img_height = 0;
	cub3d->player.x = 0;
	cub3d->player.dx = PIXELS / 2;
	cub3d->player.y = 0;
	cub3d->player.dy = PIXELS / 2;
	cub3d->player.orientation = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (!argv[1])
		arg_error();
	init(&cub3d, argv[1]);
	parse(&cub3d);
	display_window(&cub3d);
	mlx_hook(cub3d.display.mlx_win, 2, 0, key_hook, &cub3d);
	mlx_hook(cub3d.display.mlx_win, 17, 0, close_x, &cub3d);
	mlx_loop(cub3d.display.mlx);
	free_textures(&cub3d);
	free_map(&cub3d);
}
