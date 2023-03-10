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
	}
}

void	check(t_cub3d *cub3d, t_rays *ray, float x, float y)
{
	int	cx;
	int	cy;

	cx = (cub3d->player.cx + x) / PIXELS;
	cy = (cub3d->player.cy + y) / PIXELS - 1;
	dprintf(2, "!!!HERE: cx = %d, cy = %d\n", cx, cy);
	if (cub3d->map.map[cx][cy] == 1)
		dprintf(2, "WALL FOUND FIRST HORIZONTAL\n");
}

void	first_check_h(t_cub3d *cub3d, t_rays *ray, float theta)
{
	if (ray->angle > 180 && ray->angle < 360)
		ray->y = PIXELS - cub3d->player.dy;
	else
		ray->y = cub3d->player.dy;
	ray->x = ray->y / tanf(deg_to_rad(theta));
	dprintf(2, "first check horizontal %d: \nangle: %f\nx: %f\ny: %f\n\n", ray->id, ray->angle, ray->x, ray->y);
	if (ray->angle >= 0 && ray->angle < 90)
		check(cub3d, ray, ray->x, -ray->y);
	else if (ray->angle >= 90 && ray->angle < 180)
		check(cub3d, ray, -ray->x, -ray->y);
	else if (ray->angle >= 180 && ray->angle < 270)
		check(cub3d, ray, -ray->x, ray->y);
	else if (ray->angle >= 270 && ray->angle < 360)
		check(cub3d, ray, ray->x, ray->y);
	else
		dprintf(2, "ray angle is broken here\n");
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