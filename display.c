/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marie-soleiljarry <marie-soleiljarry@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:27:05 by gvial             #+#    #+#             */
/*   Updated: 2023/02/09 17:16:07 by marie-solei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_window(t_cub3d *cub3d)
{
	cub3d->display.mlx_win = \
	mlx_new_window(cub3d->display.mlx, WIDTH, HEIGHT, "Cub3d");
	print_floor(cub3d);
	print_ceiling(cub3d);
	// print_info(cub3d);
	print_minimap(cub3d);
	// print_layout(cub3d);
}

int	rgb_to_int(int *color)
{
	int	r;
	int	g;
	int	b;

	r = color[0];
	g = color[1];
	b = color[2];
	return ((r << 16) + (g << 8) + b);
}

void	print_floor(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	x = 0;
	color = rgb_to_int(cub3d->map.f_color);
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			mlx_pixel_put(cub3d->display.mlx, \
			cub3d->display.mlx_win, y, x, color);
			y++;
		}
		x++;
	}
}

void	print_ceiling(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	x = 0;
	color = rgb_to_int(cub3d->map.c_color);
	while (x < HEIGHT / 2)
	{
		y = 0;
		while (y < WIDTH)
		{
			mlx_pixel_put(cub3d->display.mlx, \
			cub3d->display.mlx_win, y, x, color);
			y++;
		}
		x++;
	}
}
