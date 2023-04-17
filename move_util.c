/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:40:10 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 13:47:08 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float degrees)
{
	return ((degrees / 180) * M_PI);
}

float	check_collision_x(t_cub3d *cub3d, float x)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(x / PIXELS);
	tile_y = (int)(cub3d->player.cy / PIXELS);
	if (cub3d->map.map[tile_y][tile_x] != 1)
		return (x);
	return (cub3d->player.cx);
}

float	check_collision_y(t_cub3d *cub3d, float y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(cub3d->player.cx / PIXELS);
	tile_y = (int)(y / PIXELS);
	if (cub3d->map.map[tile_y][tile_x] != 1)
		cub3d->player.cy = y;
	return (cub3d->player.cy);
}
