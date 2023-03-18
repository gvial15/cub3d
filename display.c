/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:27:05 by gvial             #+#    #+#             */
/*   Updated: 2023/03/15 13:03:34 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_window(t_cub3d *cub3d)
{
	cub3d->display.mlx_win = \
	mlx_new_window(cub3d->display.mlx, WIDTH, HEIGHT, "Cub3d");
	cub3d->img.img = mlx_new_image(cub3d->display.mlx, WIDTH, HEIGHT);
	cub3d->img.addr = mlx_get_data_addr(cub3d->img.img, &cub3d->img.bits_per_pixel, &cub3d->img.line_length, &cub3d->img.endian);
	cub3d->ang_incr = (float)FOV / (float)NUM_RAYS;
	print_floor(cub3d);
	print_ceiling(cub3d);
	print_minimap(cub3d);
	cast_rays(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
	x = HEIGHT / 2;
	color = rgb_to_int(cub3d->map.f_color);
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(&cub3d->img, y, x, color);
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
			my_mlx_pixel_put(&cub3d->img, y, x, color);
			y++;
		}
		x++;
	}
}
