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

void	check(t_cub3d *cub3d, t_rays *ray, float x, float y)
{
	int	cx;
	int	cy;

	cx = (cub3d->player.cx + x) / PIXELS;
	cy = (cub3d->player.cy + y) / PIXELS;
	if (ray->angle > 0 && ray->angle < 180)
		cy -= 1;
	if (ray->angle > 90 && ray->angle < 270)
		cx -= 1;
	if (cx < 0 || cx >= cub3d->map.width)
		return ;
	if (cy < 0 || cy >= cub3d->map.height)
		return ;
	dprintf(2, "checking [%d][%d]\n", cx, cy);
	if (cub3d->map.map[cy][cx] == 1)
	{
		ray->h_wall_found = 1;
		ray->wall[0] = cub3d->player.cx + x;
		ray->wall[1] = cub3d->player.cy + y;
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
	if (ray->angle > 0 && ray->angle < 180)
		ray->y = -ray->y;
	if (ray->angle > 90 && ray->angle < 270)
		ray->x = -ray->x;
	if (ray->angle == 90 || ray->angle == 270)
		ray->x = 0;
	if (ray->angle == 0 || ray->angle == 180)
		ray->y = 0;
	check(cub3d, ray, ray->x, ray->y);
	
}

void	check_horizontal(t_cub3d *cub3d, t_rays *ray)
{
	float	theta;

	theta = ray->angle;
	if (ray->angle > 90 && ray->angle < 180 || ray->angle > 270 && ray->angle < 360)
		theta = 180 - ray->angle;
	first_check_h(cub3d, ray, theta);
}

void	cast_rays(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	create_rays(cub3d);
	while (++i < NUM_RAYS)
	{
		check_horizontal(cub3d, &cub3d->rays[i]);
	}
}