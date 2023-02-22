#include "cub3d.h"

float	deg_to_rad(float degrees)
{
	return ((degrees / 180) * M_PI);
}

void	go_forward(t_cub3d *cub3d)
{
	cub3d->player.cx += cosf(deg_to_rad(cub3d->player.degrees));
	cub3d->player.cy += -sinf(deg_to_rad(cub3d->player.degrees));
	cub3d->player.dx = cub3d->player.cx / PIXELS;
	cub3d->player.dy = cub3d->player.cy / PIXELS;
	cub3d->player.x = (int)cub3d->player.cx % PIXELS;
	cub3d->player.y = (int)cub3d->player.cy % PIXELS;
}

void	go_backward(t_cub3d *cub3d)
{
	cub3d->player.cx -= cosf(deg_to_rad(cub3d->player.degrees));
	cub3d->player.cy -= -sinf(deg_to_rad(cub3d->player.degrees));
	cub3d->player.dx = cub3d->player.cx / PIXELS;
	cub3d->player.dy = cub3d->player.cy / PIXELS;
	cub3d->player.x = (int)cub3d->player.cx % PIXELS;
	cub3d->player.y = (int)cub3d->player.cy % PIXELS;
}

void	turn_left(t_cub3d *cub3d)
{
	cub3d->player.degrees += 5;
	if (cub3d->player.degrees >= 360)
		cub3d->player.degrees = 0;
}

void	turn_right(t_cub3d *cub3d)
{
	cub3d->player.degrees -= 5;
	if (cub3d->player.degrees <= -1)
		cub3d->player.degrees = 359;
}

