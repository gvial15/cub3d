/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:39:52 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 13:48:58 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_forward(t_cub3d *cub3d)
{
	float	retx;
	float	rety;

	retx = check_collision_x(cub3d, cub3d->player.cx \
			+ cosf(deg_to_rad(cub3d->player.degrees)));
	rety = check_collision_y(cub3d, cub3d->player.cy \
			- sinf(deg_to_rad(cub3d->player.degrees)));
	cub3d->player.cx = retx;
	cub3d->player.cy = rety;
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	cub3d->player.dx = cub3d->player.cx - (cub3d->player.x * PIXELS);
	cub3d->player.dy = cub3d->player.cy - (cub3d->player.y * PIXELS);
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, \
		cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	go_backward(t_cub3d *cub3d)
{
	float	retx;
	float	rety;

	retx = check_collision_x(cub3d, cub3d->player.cx \
			- cosf(deg_to_rad(cub3d->player.degrees)));
	rety = check_collision_y(cub3d, cub3d->player.cy \
			+ sinf(deg_to_rad(cub3d->player.degrees)));
	cub3d->player.cx = retx;
	cub3d->player.cy = rety;
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	cub3d->player.dx = cub3d->player.cx - (cub3d->player.x * PIXELS);
	cub3d->player.dy = cub3d->player.cy - (cub3d->player.y * PIXELS);
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, \
		cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	turn_right(t_cub3d *cub3d)
{
	cub3d->player.degrees += 5;
	if (cub3d->player.degrees >= 360)
		cub3d->player.degrees -= 360;
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, \
		cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	turn_left(t_cub3d *cub3d)
{
	cub3d->player.degrees -= 5;
	if (cub3d->player.degrees < 0)
		cub3d->player.degrees += 360;
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, \
		cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}
