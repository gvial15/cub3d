/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:15:01 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 12:17:54 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_rays(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	cub3d->rays = malloc(sizeof(t_rays) * NUM_RAYS);
	while (++i < NUM_RAYS)
	{
		cub3d->rays[i].angle = (cub3d->player.degrees - (FOV / 2)) \
								+ (i * (cub3d->ang_incr));
		if (cub3d->rays[i].angle >= 360)
			cub3d->rays[i].angle -= 360;
		if (cub3d->rays[i].angle < 0)
			cub3d->rays[i].angle += 360;
		cub3d->rays[i].x = 0;
		cub3d->rays[i].y = 0;
		cub3d->rays[i].id = i;
		cub3d->rays[i].dist = i;
		cub3d->rays[i].h_wall_found = 0;
		cub3d->rays[i].v_wall_found = 0;
		cub3d->rays[i].wall[0] = 0;
		cub3d->rays[i].wall[1] = 0;
		cub3d->is_v = 0;
		cub3d->tex_step = 0;
		cub3d->i = 0;
		cub3d->x = 0;
	}
}

void	dispatch_horiz(t_cub3d *cub3d, int i, int x)
{
	fix_fisheye(cub3d, &cub3d->rays[i]);
	if (cub3d->rays[i].angle >= 0 && cub3d->rays[i].angle <= 180)
		print_wall(cub3d, &cub3d->rays[i], x, 0);
	else
		print_wall(cub3d, &cub3d->rays[i], x, 1);
}

void	dispatch_vert(t_cub3d *cub3d, int i, int x)
{
	fix_fisheye(cub3d, &cub3d->rays[i]);
	if (cub3d->rays[i].angle >= 90 && cub3d->rays[i].angle <= 270)
		print_wall(cub3d, &cub3d->rays[i], x, 2);
	else
		print_wall(cub3d, &cub3d->rays[i], x, 3);
}

void	cast_rays(t_cub3d *cub3d)
{
	int	i;
	int	x;

	i = -1;
	create_rays(cub3d);
	while (++i < NUM_RAYS)
	{
		check_horizontal(cub3d, &cub3d->rays[i]);
		check_vertical(cub3d, &cub3d->rays[i]);
	}
	x = 0;
	i = 0;
	while (x < WIDTH && i < NUM_RAYS)
	{
		i = (float)x / ((float)WIDTH / (float)NUM_RAYS);
		if (horiz_wall(cub3d, &cub3d->rays[i]) && cub3d->rays[i].h_wall_found)
			dispatch_horiz(cub3d, i, x);
		else if (cub3d->rays[i].v_wall_found == 1)
			dispatch_vert(cub3d, i, x);
		x++;
	}
	free(cub3d->rays);
}
