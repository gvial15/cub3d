/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:23:56 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 12:24:37 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_texture(t_cub3d *cub3d, float y_i, float y_f, float tex_off)
{
	int		y;
	int		color;
	int		tex_x;
	int		tex_y;
	float	tex_pos;

	tex_pos = 0.0;
	y = y_i;
	while (y < y_f)
	{
		tex_x = tex_off * \
			((float)cub3d->textures[cub3d->i].width / (float)PIXELS);
		tex_y = (int)tex_pos;
		tex_pos += cub3d->tex_step;
		color = get_color(&cub3d->textures[cub3d->i], tex_y, tex_x);
		if (y > 0 && y < HEIGHT)
			my_mlx_pixel_put(&cub3d->img, cub3d->x, y, color);
		y++;
	}
}

void	print_wall(t_cub3d *cub3d, t_rays *ray, int x, int texture_index)
{
	float	wall_height;
	float	wall_top_pixel;
	float	wall_bottom_pixel;
	float	texture_offset;

	texture_offset = 0;
	if (texture_index == 0 || texture_index == 1)
		texture_offset = (int)ray->wall[0] - \
		((int)ray->wall[0] / PIXELS) * PIXELS;
	else if (texture_index == 2 || texture_index == 3)
		texture_offset = (int)ray->wall[1] - \
		((int)ray->wall[1] / PIXELS) * PIXELS;
	if (ray->dist <= 0.0001f)
		ray->dist = 0.0001f;
	wall_height = (5 / ray->dist) * HEIGHT;
	wall_top_pixel = ((float)HEIGHT - wall_height) / 2.0f;
	wall_bottom_pixel = wall_top_pixel + wall_height;
	cub3d->tex_step = (float)cub3d->textures[texture_index].height \
						/ wall_height;
	cub3d->x = x;
	cub3d->i = texture_index;
	draw_wall_texture(cub3d, wall_top_pixel, wall_bottom_pixel, texture_offset);
}
