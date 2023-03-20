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
	dprintf(2, "x : %f y : %f\n", (cub3d->player.cx + x), (cub3d->player.cy + y));
	dprintf(2, "cx : %d cy : %d\n", cx, cy);
	if (ray->angle >= 45 && ray->angle <= 135 && checking == 0)
		cy -= 1;
	if (ray->angle >= 135 && ray->angle <= 225 && checking == 1)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width)
	{
		dprintf(2, "here!\n");
		return (ret_zero(cub3d, ray));
	}
	if (cy < 0 || cy >= cub3d->map.height)
	{
		dprintf(2, "cx = %d map width = %d\n", cx, cub3d->map.width);
		dprintf(2, "cy = %d map height = %d\n", cy, cub3d->map.height);
		return (ret_zero(cub3d, ray));
	}
	ray->wall[0] = cub3d->player.cx + x;
	ray->wall[1] = cub3d->player.cy + y;
	dprintf(2, "checking [%d][%d]\n", cx, cy);
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
	{
		dprintf(2, "cx = %d map width = %d\n", cx, cub3d->map.width);
		dprintf(2, "cy = %d map height = %d\n", cy, cub3d->map.height);
		return (ret_zero(cub3d, ray));
	}
	if (cy < 0 || cy >= cub3d->map.height)
	{
		dprintf(2, "cx = %d map width = %d\n", cx, cub3d->map.width);
		dprintf(2, "cy = %d map height = %d\n", cy, cub3d->map.height);
		return (ret_zero(cub3d, ray));
	}
	ray->wall[0] = x;
	ray->wall[1] = y;
	dprintf(2, "%f degrees : checking [%d][%d]\n", ray->angle, cx, cy);
	if (cub3d->map.map[cy][cx] == 1)
		return (1);
	return (0);
}

void	loop_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	ray->y = PIXELS;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	fix_sign(ray);
	dprintf(2, "%f degrees: horiz x-step = %f, horiz y_step = %f\n", ray->angle, ray->x, ray->y);
	while (!ray->h_wall_found)
	{
		dprintf(2, "last checked position horiz: (%f, %f)\n", ray->h_check[0], ray->h_check[1]);
		ray->h_wall_found = check_l(cub3d, ray, ray->h_check[0] + ray->x, ray->h_check[1] + ray->y, 0);
		// if (ray->wall[0] == 0 && ray->wall[1] == 0)
		// 	return ;
		ray->h_check[0] = ray->wall[0];
		ray->h_check[1] = ray->wall[1];
		if (ray->h_check[0] == 0 && ray->h_check[1] == 0)
			return ;
		if (ray->h_wall_found == 1)
			dprintf(2, "ray #%d: horizontal wall found at [%f][%f]\n", ray->id, ray->h_check[0], ray->h_check[1]);
	}
}

void	loop_check_v(t_cub3d *cub3d, t_rays *ray, float theta)
{
	ray->x = PIXELS;
	ray->y = ray->x * tanf(deg_to_rad(theta));
	fix_sign(ray);
	dprintf(2, "%f degrees: vert x-step = %f, vert y_step = %f\n", ray->angle, ray->x, ray->y);
	while (!ray->v_wall_found)
	{
		dprintf(2, "last checked position vert: (%f, %f)\n", ray->v_check[0], ray->v_check[1]);
		ray->v_wall_found = check_l(cub3d, ray, ray->v_check[0] + ray->x, ray->v_check[1] + ray->y, 1);

		// if (ray->wall[0] == 0 && ray->wall[1] == 0)
		// 	return ;
		ray->v_check[0] = ray->wall[0];
		ray->v_check[1] = ray->wall[1];
		if (ray->v_check[0] == 0 && ray->v_check[1] == 0)
			return ;
		if (ray->v_wall_found == 1)
			dprintf(2, "ray #%d: vertical wall found at [%f][%f]\n", ray->id, ray->v_check[0], ray->v_check[1]);
	}
}

void	first_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if (ray->angle > 180 && ray->angle < 360)
		ray->y = PIXELS - cub3d->player.dy;
	else
		ray->y = cub3d->player.dy;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	// dprintf(2, "first check horizontal %d: \nangle: %f\nx: %f\ny: %f\n\n", ray->id, ray->angle, ray->x, ray->y);
	fix_sign(ray);
	ray->h_wall_found = check(cub3d, ray, ray->x, ray->y, 0);
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
	// dprintf(2, "first check horizontal %d: \nangle: %f\nx: %f\ny: %f\n\n", ray->id, ray->angle, ray->x, ray->y);
	fix_sign(ray);
	ray->v_wall_found = check(cub3d, ray, ray->x, ray->y, 1);
	ray->v_check[0] = ray->wall[0];
	ray->v_check[1] = ray->wall[1];
}

void	check_horizontal(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if (ray->angle > 90 && ray->angle < 180 || ray->angle > 270 && ray->angle < 360)
		theta = 360 - ray->angle;
	dprintf(2, "HORIZONTAL :::::: \n");
	first_check_h(cub3d, ray, theta);
	// dprintf(2, "horizontal wall found? : %d\n", ray->h_wall_found);
	if (!ray->h_wall_found)
		loop_check_h(cub3d, ray, theta);
	else
		dprintf(2, "%f : horiz found on first check at [%f][%f]\n", ray->angle, ray->h_check[0], ray->h_check[1]);
}

void	check_vertical(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if ((ray->angle > 90 && ray->angle < 180) || (ray->angle > 270 && ray->angle < 360))
		theta = 360 - ray->angle;
	dprintf(2, "VERTICAL :::::: \n");
	first_check_v(cub3d, ray, theta);
	// dprintf(2, "vertical wall found? : %d\n", ray->v_wall_found);
	if (!ray->v_wall_found)
		loop_check_v(cub3d, ray, theta);
	else
		dprintf(2, "%f : vert found on first check at [%f][%f]\n", ray->angle, ray->v_check[0], ray->v_check[1]);
}

int	horiz_wall(t_cub3d *cub3d, t_rays *ray)
{
	float	h_dist;
	float	v_dist;

	h_dist = sqrtf(powf(ray->h_check[1] - cub3d->player.cy, 2) + powf(ray->h_check[0] - cub3d->player.cx, 2));
	v_dist = sqrtf(powf(ray->v_check[1] - cub3d->player.cy, 2) + powf(ray->v_check[0] - cub3d->player.cx, 2));
	if (!ray->v_wall_found || h_dist < v_dist)
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

void	print_wall(t_cub3d *cub3d, t_rays *ray, int color)
{
	float	wall_height;
	float	wall_width;
	float	i;
	float	x;

	if (ray->dist <= 0.0001)
		ray->dist = 0.0001;
	wall_height = (5 / ray->dist) * HEIGHT;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	wall_width = (float)WIDTH / (float)NUM_RAYS;
	x = ray->id * wall_width;
	while (x < wall_width * (ray->id + 1) && x <= (WIDTH + 1))
	{
		i = (HEIGHT / 2) - (wall_height / 2);
		while (i <= (HEIGHT / 2) + (wall_height / 2))
		{
			my_mlx_pixel_put(&cub3d->img, x, i, color);
			i++;
		}
		x++;
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
			if (cub3d->rays[i].angle > 0 && cub3d->rays[i].angle < 180)
				print_wall(cub3d, &cub3d->rays[i], 0xD3D3D3); //north
			else
				print_wall(cub3d, &cub3d->rays[i], 0x5A5A5A); //south
		}
		else if (cub3d->rays[i].v_wall_found == 1)
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			if (cub3d->rays[i].angle > 90 && cub3d->rays[i].angle < 270)
				print_wall(cub3d, &cub3d->rays[i], 0xCBC3E3); //west
			else
				print_wall(cub3d, &cub3d->rays[i], 0x301934); //east
		}
		i++;
	}
	// mlx_destroy_image(cub3d->display.mlx, &cub3d->img);
	free(cub3d->rays);
}