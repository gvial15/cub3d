#include "cub3d.h"

float	deg_to_rad(float degrees)
{
	return ((degrees / 180) * M_PI);
}

void	go_forward(t_cub3d *cub3d)
{
	cub3d->player.cx += cosf(deg_to_rad(cub3d->player.degrees)) * 3;
	cub3d->player.cy += -sinf(deg_to_rad(cub3d->player.degrees)) *3;
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	cub3d->player.dx = cub3d->player.cx - (cub3d->player.x * PIXELS);
	cub3d->player.dy = cub3d->player.cy - (cub3d->player.y * PIXELS);
	dprintf(2, "dx: %f\ndy: %f\n", cub3d->player.cx, cub3d->player.cy);
	// print_floor(cub3d);
	// print_ceiling(cub3d);
	cast_rays(cub3d);
}

void	go_backward(t_cub3d *cub3d)
{
	cub3d->player.cx -= cosf(deg_to_rad(cub3d->player.degrees)) * 3;
	cub3d->player.cy -= -sinf(deg_to_rad(cub3d->player.degrees)) * 3;
	cub3d->player.dx = (int)cub3d->player.cx % PIXELS;
	cub3d->player.dy = (int)cub3d->player.cy % PIXELS;
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	dprintf(2, "dx: %f\ndy: %f\n", cub3d->player.cx, cub3d->player.cy);
	// print_floor(cub3d);
	// print_ceiling(cub3d);
	cast_rays(cub3d);
}

void	turn_left(t_cub3d *cub3d)
{
	cub3d->player.degrees += 5;
	if (cub3d->player.degrees >= 360)
		cub3d->player.degrees -= 360;
	// print_floor(cub3d);
	// print_ceiling(cub3d);
	cast_rays(cub3d);
}

void	turn_right(t_cub3d *cub3d)
{
	cub3d->player.degrees -= 5;
	if (cub3d->player.degrees < 0)
		cub3d->player.degrees += 360;
	// print_floor(cub3d);
	// print_ceiling(cub3d);
	cast_rays(cub3d);
}

