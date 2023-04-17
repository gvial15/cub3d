/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:09:51 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 13:17:12 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fix_sign(t_rays *ray)
{
	if (ray->angle > 0 && ray->angle < 180)
		ray->y = -ray->y;
	if (ray->angle > 90 && ray->angle < 270)
		ray->x = -ray->x;
	if (ray->angle == 90 || ray->angle == 270)
		ray->x = 0;
	if (ray->angle == 0 || ray->angle == 180)
		ray->y = 0;
}

int	ret_zero(t_rays *ray)
{
	ray->wall[0] = 0;
	ray->wall[1] = 0;
	return (0);
}

void	fix_fisheye(t_cub3d *cub3d, t_rays *ray)
{
	ray->dist = roundf((ray->dist * \
	cosf(deg_to_rad(ray->angle - cub3d->player.degrees)) * 100000)) / 100000;
}

int	get_color(t_texture *text, int y, int x)
{
	if (x >= text->width)
		x = text->width - 1;
	if (y >= text->height)
		y = text->height - 1;
	return (text->texture[y][x]);
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
