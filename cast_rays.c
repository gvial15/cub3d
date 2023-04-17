/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:15:01 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 09:24:14 by mjarry           ###   ########.fr       */
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
		cub3d->rays[i].angle = (cub3d->player.degrees - (FOV/2)) + (i * (cub3d->ang_incr));
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
		cub3d->wall_i[0] = 0;
		cub3d->wall_i[1] = 0;
		cub3d->wall_i[2] = 0;
		cub3d->wall_i[3] = 0;
	}
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
		dprintf(2, "x: %d   i: %d\n", x, i);
		if (horiz_wall(cub3d, &cub3d->rays[i]) && cub3d->rays[i].h_wall_found)
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			if (cub3d->rays[i].angle >= 0 && cub3d->rays[i].angle <= 180)
				print_wall(cub3d, &cub3d->rays[i], x, 0); //north
			else
				print_wall(cub3d, &cub3d->rays[i], x, 1); //south
		}
		else if (cub3d->rays[i].v_wall_found == 1)
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			if (cub3d->rays[i].angle >= 90 && cub3d->rays[i].angle <= 270)
				print_wall(cub3d, &cub3d->rays[i], x, 2); //west
			else
				print_wall(cub3d, &cub3d->rays[i], x, 3); //east
		}
		x++;
	}
	free(cub3d->rays);
}