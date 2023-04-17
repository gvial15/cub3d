/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:15:01 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/17 08:38:14 by mjarry           ###   ########.fr       */
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

int	check(t_cub3d *cub3d, t_rays *ray, float x, float y, int checking)
{
	int		cx;
	int		cy;

	cx = (cub3d->player.cx + x) / PIXELS;
	cy = (cub3d->player.cy + y) / PIXELS;
	if (ray->angle >= 0 && ray->angle <= 180 && checking == 0)
		cy -= 1;
	if (ray->angle >= 90 && ray->angle <= 270 && checking == 1)
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

int	check_l(t_cub3d *cub3d, t_rays *ray, float x, float y, int checking)
{
	int	cx;
	int	cy;

	if (x <= 0 || (x / PIXELS) >= cub3d->map.width || y <= 0 || (y / PIXELS) >= cub3d->map.height)
		return (ret_zero(ray));
	cx = x / PIXELS;
	cy = y / PIXELS;
	if (ray->angle > 0 && ray->angle < 180 && checking == 0)
		cy -= 1;
	if (ray->angle > 90 && ray->angle < 270 && checking == 1)
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

void	loop_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	ray->y = PIXELS;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	fix_sign(ray);
	while (!ray->h_wall_found)
	{
		ray->h_wall_found = check_l(cub3d, ray, ray->h_check[0] + ray->x, ray->h_check[1] + ray->y, 0);
		ray->h_check[0] = ray->wall[0];
		ray->h_check[1] = ray->wall[1];
		if (ray->h_check[0] <= (float)0 && ray->h_check[1] <= (float)0)
		{
			ray->h_wall_found = 0;
			return ;
		}
	}
}

void	loop_check_v(t_cub3d *cub3d, t_rays *ray, float theta)
{
	ray->x = PIXELS;
	ray->y = ray->x * tanf(deg_to_rad(theta));
	fix_sign(ray);
	while (!ray->v_wall_found)
	{
		ray->v_wall_found = check_l(cub3d, ray, ray->v_check[0] + ray->x, ray->v_check[1] + ray->y, 1);
		ray->v_check[0] = ray->wall[0];
		ray->v_check[1] = ray->wall[1];
		if (ray->v_check[0] <= (float)0 && ray->v_check[1] <= (float)0)
		{
			ray->v_wall_found = 0;
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
	ray->h_wall_found = check(cub3d, ray, ray->x, ray->y, 0);
	if (ray->wall[0] == (float)0 || ray->wall[1] == (float)0)
		ray->h_wall_found = 0;
	ray->h_check[0] = ray->wall[0];
	ray->h_check[1] = ray->wall[1];
}

void	first_check_v(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if ((ray->angle >= 0 && ray->angle <= 90) || (ray->angle >= 270 && ray->angle < 360))
		ray->x = PIXELS - cub3d->player.dx;
	else
		ray->x = cub3d->player.dx;
	ray->y = ray->x * tanf(deg_to_rad(theta));
	fix_sign(ray);
	ray->v_wall_found = check(cub3d, ray, ray->x, ray->y, 1);
	if (ray->wall[0] == (float)0 || ray->wall[1] == (float)0)
		ray->v_wall_found = 0;
	ray->v_check[0] = ray->wall[0];
	ray->v_check[1] = ray->wall[1];
}

void	check_horizontal(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if ((ray->angle > 90 && ray->angle < 180) || (ray->angle > 270 && ray->angle < 360))
		theta = 360 - ray->angle;
	first_check_h(cub3d, ray, theta);
	if (!ray->h_wall_found && ray->h_check[0] != (float)0 && ray->h_check[1] != (float)0)
		loop_check_h(cub3d, ray, theta);
}

void	check_vertical(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if ((ray->angle > 90 && ray->angle < 180) || (ray->angle > 270 && ray->angle < 360))
		theta = 360 - ray->angle;
	first_check_v(cub3d, ray, theta);
	if (!ray->v_wall_found && ray->v_check[0] != (float)0 && ray->v_check[1] != (float)0)
		loop_check_v(cub3d, ray, theta);
}

int	horiz_wall(t_cub3d *cub3d, t_rays *ray)
{
	float	h_dist;
	float	v_dist;

	h_dist = sqrtf(powf(ray->h_check[1] - cub3d->player.cy, 2) + powf(ray->h_check[0] - cub3d->player.cx, 2));
	v_dist = sqrtf(powf(ray->v_check[1] - cub3d->player.cy, 2) + powf(ray->v_check[0] - cub3d->player.cx, 2));
	if (!ray->v_wall_found || (h_dist < v_dist && (ray->h_check[1] && ray->h_check[0])))
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

void	fix_fisheye(t_cub3d *cub3d, t_rays *ray)
{
	ray->dist = roundf((ray->dist * cosf(deg_to_rad(ray->angle - cub3d->player.degrees)) * 100000)) / 100000;
}

int get_color(t_texture *text, int y, int x)
{
	if (x >= text->width)
		x = text->width - 1;
	if (y >= text->height)
		y = text->height - 1;
   return(text->texture[y][x]);
}

void	draw_wall_texture(t_cub3d *cub3d, int x, float y_start, float y_end, int i, float texture_offset, float tex_step)
{
	int		y;
	float	tex_pos;

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