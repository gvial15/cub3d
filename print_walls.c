/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:23:56 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 09:24:11 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_texture(t_cub3d *cub3d, int x, float y_start, float y_end, int i, float texture_offset, float tex_step)
{
	int		y;
	float	tex_pos;
	int		color;

	tex_pos = 0.0;
	y = y_start;
	while (y < y_end)
	{
		int tex_x = texture_offset * ((float)cub3d->textures[i].width / (float)PIXELS);
		int tex_y = (int)tex_pos;
		tex_pos += tex_step;
		color = get_color(&cub3d->textures[i], tex_y, tex_x);
		if (y > 0 && y < HEIGHT)
			my_mlx_pixel_put(&cub3d->img, x, y, color);

		y++;
	}
}

void	print_wall(t_cub3d *cub3d, t_rays *ray, int x, int texture_index)
{
    float	wall_height;
    float 	wall_top_pixel;
    float 	wall_bottom_pixel;
    float 	texture_offset;
	float	tex_step;

	texture_offset = 0;
	if (texture_index == 0 || texture_index == 1)
		texture_offset = (int)ray->wall[0] - ((int)ray->wall[0] / PIXELS) * PIXELS;
	else if (texture_index == 2 || texture_index == 3)
		texture_offset = (int)ray->wall[1] - ((int)ray->wall[1] / PIXELS) * PIXELS;
   	if (ray->dist <= 0.0001f)
		ray->dist = 0.0001f;
	wall_height = (5 / ray->dist) * HEIGHT;
    wall_top_pixel = ((float)HEIGHT - wall_height) / 2.0f;
    wall_bottom_pixel = wall_top_pixel + wall_height;
	tex_step = (float)cub3d->textures[texture_index].height / wall_height;
    draw_wall_texture(cub3d, x, wall_top_pixel, wall_bottom_pixel, texture_index, texture_offset, tex_step);
}