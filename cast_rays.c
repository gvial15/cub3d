/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:15:01 by mjarry            #+#    #+#             */
/*   Updated: 2023/04/04 13:27:16 by mjarry           ###   ########.fr       */
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

int	ret_zero(t_cub3d * cub3d, t_rays *ray)
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
		return (ret_zero(cub3d, ray));
	if (cy < 0 || cy >= cub3d->map.height || (cub3d->player.cy + y) < 0)
		return (ret_zero(cub3d, ray));
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
		return (ret_zero(cub3d, ray));
	cx = x / PIXELS;
	cy = y / PIXELS;
	if (ray->angle > 0 && ray->angle < 180 && checking == 0)
		cy -= 1;
	if (ray->angle > 90 && ray->angle < 270 && checking == 1)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width)
		return (ret_zero(cub3d, ray));
	if (cy < 0 || cy >= cub3d->map.height)
		return (ret_zero(cub3d, ray));
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
	if (ray->angle > 90 && ray->angle < 180 || ray->angle > 270 && ray->angle < 360)
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
	if (!ray->v_wall_found || h_dist < v_dist && (ray->h_check[1] && ray->h_check[0]))
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
	// ********
	// dprintf(2, "%f degrees : Wall distance = %f\n", ray->angle, ray->dist);
	// dprintf(2, "wall coordinates: (%f, %f)\n", ray->wall[0], ray->wall[1]);
}

// int	get_color(t_cub3d *cub3d, t_texture texture, float x, float i)
// {
// 	int j;
// 	int y;

// 	j = x - ((int)(x / PIXELS) * PIXELS);
// 	y = (int)i % 25;
// 	// if (y >= 25)
// 	// 	y %= 25;
// 	if (j >= 25)
// 		j %= 25;
// 	// y = (int)y % texture.height;
// 	// j = (int)j % texture.width;
// 	// dprintf(2, "%d, %d\n", (int)j, (int)y);
// 	// return (0x00FF00);
// 	return (texture.texture[j][y]);
// }

int get_color(t_cub3d *cub3d, int i, int y, int x)
{
	// dprintf(2, "%d, %d\n", y, x);
   return(cub3d->textures[i].texture[y][x]);
}

// void	printing_texture(t_cub3d *cub3d, t_rays *ray, int i, float wall_height, float y, float x)
// {
// 	int	tx = (int)ray->wall[0] - ((int)ray->wall[0] / PIXELS) * PIXELS;
// 	int	ty = (int)ray->wall[1] - ((int)ray->wall[1] / PIXELS) * PIXELS;
// 	int	pix_x = ty;
// 	int	pix_y = wall_height / PIXELS;
// 	if (ty == 0)
// 		pix_x = tx;
// 	my_mlx_pixel_put(&cub3d->img, x, y, cub3d->textures[i].texture[pix_x][pix_y]);
// }
// ---------------------------------------------------------------------------
void	print_wall(t_cub3d *cub3d, t_rays *ray, t_texture *texture, int i)
{
	float	wall_height;
	float	wall_width;
	float	y;
	float	x;
	int	tx = (int)ray->wall[0] - ((int)ray->wall[0] / PIXELS) * PIXELS;
	int	ty = (int)ray->wall[1] - ((int)ray->wall[1] / PIXELS) * PIXELS;
	int	starter = ty;
	int	rat_x = PIXELS / 25;
	int	rat_y;
	int h = 0;
	int	rem_x = 0;
	int h_cnt;
	int	color;
	int rc = 0;
	if (ty == 0)
		starter = tx;

	if (ray->dist <= 0.0001)
		ray->dist = 0.0001;
	wall_height = (5 / ray->dist) * HEIGHT;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	rat_y = wall_height / 25;
	wall_width = (float)WIDTH / (float)NUM_RAYS;
	x = ray->id * wall_width;
	if ((PIXELS % 25) != 0)
		rem_x = PIXELS / (PIXELS % 25);
	while (x < wall_width * (ray->id + 1) && x <= (WIDTH + 1))
	{
		y = (HEIGHT / 2) - (wall_height / 2);
		h_cnt = 0;
		h = 0;
		while (y <= (HEIGHT / 2) + (wall_height / 2) && h < 25)
		{
			// printing_texture(cub3d, ray, i, wall_height, y, x);
			dprintf(2, "%f: %d , %d\n", wall_height,  h_cnt, starter);
			color = get_color(cub3d, i, h, starter);
			my_mlx_pixel_put(&cub3d->img, x, y, color);
			h_cnt++;
			y++;
			while (h_cnt < rat_y)
			{
				my_mlx_pixel_put(&cub3d->img, x, y, color);
				h_cnt++;
				y++;
			}
			h++;
			h_cnt = 0;
		}
		// if (rem_x != 0 && rc % rem_x == 0)
		// {
		// 	// dprintf(2, "%d , %d\n", h_cnt, starter);
		// 	color = get_color(cub3d, i, (h_cnt / rat_y), starter);
		// 	my_mlx_pixel_put(&cub3d->img, ++x, y, color);
		// 	h_cnt++;
		// 	y++;
		// 	while ((h_cnt) % rat_y != 0)
		// 	{
		// 		my_mlx_pixel_put(&cub3d->img, ++x, y, color);
		// 		h_cnt++;
		// 		y++;
		// 	}
		// }
		starter++;
		rc++;
		if (starter >= 25)
			starter = 0;
		x++;
	}
}
// ---------------------------------------------------------------------------

								// void    print_wall(t_cub3d *cub3d, t_rays *ray, t_texture *texture, int i)
								// {
								// 	float   wall_height;
								// 	float   wall_width;
								// 	float   y;
								// 	float   x;
								// // ----------------------------------------
								// 	int     wx = (int)ray->wall[0] - ((int)ray->wall[0] / PIXELS) * PIXELS;
								// 	int     wy = (int)ray->wall[1] - ((int)ray->wall[1] / PIXELS) * PIXELS;
								// 	int  starter_x = wy;
								// 	if (wy == 0)
								// 		starter_x = wx;
								// 	int h_ratio = wall_height / 25; //texture_height;
								// 	int vy = 0;
								// 	int h_count = 0;
								// // ----------------------------------------
								// 	if (ray->dist <= 0.0001)
								// 		ray->dist = 0.0001;
								// 	wall_height = (5 / ray->dist) * HEIGHT;
								// 	if (wall_height > HEIGHT)
								// 		wall_height = HEIGHT;
								// 	wall_width = (float)WIDTH / (float)NUM_RAYS;
								// 	x = ray->id * wall_width;
								// 	while (x < wall_width * (ray->id + 1))
								// 	{
								// 		y = (HEIGHT / 2) - (wall_height / 2);
								// 		while (y <= (HEIGHT / 2) + (wall_height / 2))
								// 		{
								// 			h_count = 0;
								// 			// printf("Starter_x = %d | vy = %d\n");
								// 			while (h_count < h_ratio)
								// 			{
								// 				my_mlx_pixel_put(&cub3d->img, x, y, cub3d->textures[i].texture[starter_x][vy]);
								// 				y++;
								// 				h_count++;
								// 			}
								// 	// printf("HERE\n");
								// 			vy++;
								// 		}
								// 		x++;
								// 	}
								// }
// ---------------------------------------------------------------------------

// void	print_wall(t_cub3d *cub3d, t_rays *ray, t_texture texture, int i)
// {
	// float	wall_height;
	// float	wall_width;
	// float	y;
	// float	x;
// 	int		height_ratio;
// 	int		color;
// 	int		cnt;

// 	cub3d->wall_j = 0;
// 	if (ray->dist <= 0.0001)
// 		ray->dist = 0.0001;
// 	wall_height = (5 / ray->dist) * HEIGHT;
// 	if (wall_height > HEIGHT)
// 		wall_height = HEIGHT;
// 	height_ratio = wall_height / 25;
// 	wall_width = (float)WIDTH / (float)NUM_RAYS;
// 	x = ray->id * wall_width;
// 	while (x < wall_width * (ray->id + 1) && x <= (WIDTH + 1))
// 	{
// 		y = (HEIGHT / 2) - (wall_height / 2);
// 		while (y <= (HEIGHT / 2) + (wall_height / 2))
// 		{
// 			cnt = 0;
// 			cub3d->wall_j = 0;
// 			while (cnt < height_ratio && y <= (HEIGHT / 2) + (wall_height / 2))
// 			{
// 				color = get_color(cub3d, i);
// 				my_mlx_pixel_put(&cub3d->img, x, y, color);
// 				y++;
// 				cnt++;
// 			}
// 			cub3d->wall_j++;
// 		}
// 		x++;
// 		(cub3d->wall_i[i])++;
// 		if (cub3d->wall_i[i] >= 25)
// 			cub3d->wall_i[i] = 0;
// 	}
// }

void	draw_line(t_cub3d *cub3d, float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	step;
	float	x;
	float	y;
	int		i;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	step = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);
	delta_x /= step;
	delta_y /= step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(&cub3d->img, x, y, 0x00FFFF);
		x += delta_x;
		y += delta_y;
		i++;
	}
}

//REMEMBER TO DESTROY IMAGES
void	cast_rays(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	create_rays(cub3d);
	while (i < NUM_RAYS)
	{
		check_horizontal(cub3d, &cub3d->rays[i]);
		check_vertical(cub3d, &cub3d->rays[i]);
		if (horiz_wall(cub3d, &cub3d->rays[i]) && cub3d->rays[i].h_wall_found)
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			if (cub3d->rays[i].angle >= 0 && cub3d->rays[i].angle <= 180)
				print_wall(cub3d, &cub3d->rays[i], &cub3d->textures[0], 0); //north
			else
				print_wall(cub3d, &cub3d->rays[i], &cub3d->textures[1], 1); //south
		}
		else if (cub3d->rays[i].v_wall_found == 1)
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			if (cub3d->rays[i].angle >= 90 && cub3d->rays[i].angle <= 270)
				print_wall(cub3d, &cub3d->rays[i], &cub3d->textures[2], 2); //west
			else
				print_wall(cub3d, &cub3d->rays[i], &cub3d->textures[3], 3); //east
		}
		i++;
	}
	// mlx_destroy_image(cub3d->display.mlx, &cub3d->img);
	free(cub3d->rays);
}