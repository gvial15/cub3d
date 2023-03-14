#include "cub3d.h"

void	create_rays(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	cub3d->rays = malloc(sizeof(t_rays) * NUM_RAYS);
	while (++i < NUM_RAYS)
	{
		cub3d->rays[i].angle = (cub3d->player.degrees - (FOV/2)) + (i * ((float)FOV / (float)NUM_RAYS));
		cub3d->rays[i].x = 0;
		cub3d->rays[i].y = 0;
		cub3d->rays[i].id = i;
		cub3d->rays[i].h_wall_found = 0;
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

int	check(t_cub3d *cub3d, t_rays *ray, float x, float y)
{
	int		cx;
	int		cy;

	cx = (cub3d->player.cx + x) / PIXELS;
	cy = (cub3d->player.cy + y) / PIXELS;
	if (ray->angle > 0 && ray->angle < 180)
		cy -= 1;
	if (ray->angle > 90 && ray->angle < 270)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width)
		return (0);
	if (cy < 0 || cy >= cub3d->map.height)
		return (0);
	ray->wall[0] = cub3d->player.cx + x;
	ray->wall[1] = cub3d->player.cy + y;
	dprintf(2, "checking [%d][%d]\n", cx, cy);
	if (cub3d->map.map[cy][cx] == 1)
		return (1);
	return (0);
}

// void	loop_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
// {
// 	while (!ray->h_wall_found)
// 	{

// 	}
// }

void	first_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if (ray->angle > 180 && ray->angle < 360)
		ray->y = PIXELS - cub3d->player.dy;
	else
		ray->y = cub3d->player.dy;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	// dprintf(2, "first check horizontal %d: \nangle: %f\nx: %f\ny: %f\n\n", ray->id, ray->angle, ray->x, ray->y);
	fix_sign(ray);
	ray->h_wall_found = check(cub3d, ray, ray->x, ray->y);
	ray->h_check[0] = ray->wall[0];
	ray->h_check[1] = ray->wall[1];
}

void	first_check_v(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if (ray->angle > 0 && ray->angle < 90 || ray->angle > 270 && ray->angle < 360)
		ray->x = PIXELS - cub3d->player.dx;
	else
		ray->x = cub3d->player.dx;
	ray->y = ray->x * tanf(deg_to_rad(theta));
	// dprintf(2, "first check horizontal %d: \nangle: %f\nx: %f\ny: %f\n\n", ray->id, ray->angle, ray->x, ray->y);
	fix_sign(ray);
	ray->v_wall_found = check(cub3d, ray, ray->x, ray->y);
	ray->v_check[0] = ray->wall[0];
	ray->v_check[1] = ray->wall[1];
}

void	check_horizontal(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if (ray->angle > 90 && ray->angle < 180 || ray->angle > 270 && ray->angle < 360)
		theta = 180 - ray->angle;
	first_check_h(cub3d, ray, theta);
	// if (!ray->h_wall_found)
		// loop_check_h(cub3d, ray, theta);
}

void	check_vertical(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if (ray->angle > 90 && ray->angle < 180 || ray->angle > 270 && ray->angle < 360)
		theta = 180 - ray->angle;
	first_check_v(cub3d, ray, theta);
	// if (!ray->v_wall_found)
	// 	loop_check_v(cub3d, ray, theta);
}

int	horiz_wall(t_cub3d *cub3d, t_rays *ray)
{
	// if horiz < vert ret 1
	float	h_dist;
	float	v_dist;

	h_dist = sqrtf(powf(ray->h_check[1] - cub3d->player.cy, 2) + powf(ray->h_check[0] - cub3d->player.cx, 2));
	v_dist = sqrtf(powf(ray->v_check[1] - cub3d->player.cy, 2) + powf(ray->v_check[0] - cub3d->player.cx, 2));
	if (!ray->v_wall_found || h_dist < v_dist) //if == , corner??
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
	dprintf(2, "distance finale = %f\n", ray->dist);
	ray->dist = ray->dist * cosf(deg_to_rad(ray->angle - cub3d->player.degrees));
}

void	cast_rays(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	create_rays(cub3d);
	while (++i < NUM_RAYS)
	{
		check_horizontal(cub3d, &cub3d->rays[i]);
		check_vertical(cub3d, &cub3d->rays[i]);
		//distance horizontal vs vertical
		dprintf(2, "horizontal wall found for %f degrees: (%f, %f)\n", cub3d->rays[i].angle, cub3d->rays[i].h_check[0], cub3d->rays[i].h_check[1]);
		dprintf(2, "vertical wall found for %f degrees: (%f, %f)\n", cub3d->rays[i].angle, cub3d->rays[i].v_check[0], cub3d->rays[i].v_check[1]);
		// mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, (int)cub3d->rays[i].v_check[0], cub3d->rays[i].v_check[1], 0xFF00FF);
		if (cub3d->rays[i].h_wall_found && horiz_wall(cub3d, &cub3d->rays[i]))
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			// if (cub3d->rays[i].angle > 0 && cub3d->rays[i].angle < 180)
			// 	north_wall(cub3d, &cub3d->rays[i]);
			// else
			// 	south_wall(cub3d, &cub3d->rays[i]);
		}
		else
		{
			fix_fisheye(cub3d, &cub3d->rays[i]);
			// if (cub3d->rays[i].angle > 90 && cub3d->rays[i].angle < 270)
			// 	west_wall(cub3d, &cub3d->rays[i]);
			// else
			// 	east_wall(cub3d, &cub3d->rays[i]);
		}
	}
}