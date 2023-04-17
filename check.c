/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:12:50 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 10:57:14 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check(t_cub3d *cub3d, t_rays *ray, float x, float y)
{
	int		cx;
	int		cy;

	cx = (cub3d->player.cx + x) / PIXELS;
	cy = (cub3d->player.cy + y) / PIXELS;
	if (ray->angle >= 0 && ray->angle <= 180 && cub3d->is_v == 0)
		cy -= 1;
	if (ray->angle >= 90 && ray->angle <= 270 && cub3d->is_v == 1)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width || cub3d->player.cx + x < 0)
		return (ret_zero(ray));
	if (cy < 0 || cy >= cub3d->map.height || (cub3d->player.cy + y) < 0)
		return (ret_zero(ray));
	ray->wall[0] = cub3d->player.cx + x;
	ray->wall[1] = cub3d->player.cy + y;
	if (cub3d->map.map[cy][cx] == 1)
		return (1);
	return (0);
}

int	check_l(t_cub3d *cub3d, t_rays *ray, float x, float y)
{
	int	cx;
	int	cy;

	if (x <= 0 || (x / PIXELS) >= cub3d->map.width || y <= 0
		|| (y / PIXELS) >= cub3d->map.height)
		return (ret_zero(ray));
	cx = x / PIXELS;
	cy = y / PIXELS;
	if (ray->angle > 0 && ray->angle < 180 && cub3d->is_v == 0)
		cy -= 1;
	if (ray->angle > 90 && ray->angle < 270 && cub3d->is_v == 1)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width)
		return (ret_zero(ray));
	if (cy < 0 || cy >= cub3d->map.height)
		return (ret_zero(ray));
	ray->wall[0] = x;
	ray->wall[1] = y;
	if (cub3d->map.map[cy][cx] == 1)
		return (1);
	return (0);
}
