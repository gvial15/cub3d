/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:17:40 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 12:11:03 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	ray->y = PIXELS;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	fix_sign(ray);
	while (!ray->h_wall_found)
	{
		cub3d->is_v = 0;
		ray->h_wall_found = check_l(cub3d, ray, \
		ray->h_check[0] + ray->x, ray->h_check[1] + ray->y);
		ray->h_check[0] = ray->wall[0];
		ray->h_check[1] = ray->wall[1];
		if (ray->h_check[0] <= (float)0 && ray->h_check[1] <= (float)0)
		{
			ray->h_wall_found = 0;
			return ;
		}
	}
}

void	first_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if (ray->angle > 180 && ray->angle < 360)
		ray->y = PIXELS - cub3d->player.dy;
	else
		ray->y = cub3d->player.dy;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	fix_sign(ray);
	cub3d->is_v = 0;
	ray->h_wall_found = check(cub3d, ray, ray->x, ray->y);
	if (ray->wall[0] == (float)0 || ray->wall[1] == (float)0)
		ray->h_wall_found = 0;
	ray->h_check[0] = ray->wall[0];
	ray->h_check[1] = ray->wall[1];
}

void	check_horizontal(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if ((ray->angle > 90 && ray->angle < 180)
		|| (ray->angle > 270 && ray->angle < 360))
		theta = 360 - ray->angle;
	first_check_h(cub3d, ray, theta);
	if (!ray->h_wall_found && ray->h_check[0] != (float)0
		&& ray->h_check[1] != (float)0)
		loop_check_h(cub3d, ray, theta);
}

int	horiz_wall(t_cub3d *cub3d, t_rays *ray)
{
	float	h_dist;
	float	v_dist;

	h_dist = sqrtf(powf(ray->h_check[1] - cub3d->player.cy, 2) \
			+ powf(ray->h_check[0] - cub3d->player.cx, 2));
	v_dist = sqrtf(powf(ray->v_check[1] - cub3d->player.cy, 2) \
			+ powf(ray->v_check[0] - cub3d->player.cx, 2));
	if (!ray->v_wall_found || (h_dist < v_dist
			&& (ray->h_check[1] && ray->h_check[0])))
	{
		ray->dist = h_dist;
		ray->wall[0] = ray->h_check[0];
		ray->wall[1] = ray->h_check[1];
		return (1);
	}
	ray->dist = v_dist;
	ray->wall[0] = ray->v_check[0];
	ray->wall[1] = ray->v_check[1];
	return (0);
}
