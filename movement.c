#include "cub3d.h"

float	deg_to_rad(float degrees)
{
	return ((degrees / 180) * M_PI);
}

void	check_collision_x(t_cub3d *cub3d, float x)
{
    int		tile_x;
    int		tile_y;

    tile_x = (int)x / PIXELS;
    tile_y = (int)cub3d->player.cy / PIXELS;

    if (cub3d->map.map[tile_y][tile_x] != 1)
        cub3d->player.cx = x;
}

void	check_collision_y(t_cub3d *cub3d, float y)
{
    int		tile_x;
    int		tile_y;

    tile_x = (int)cub3d->player.cx / PIXELS;
    tile_y = (int)y / PIXELS;

    if (cub3d->map.map[tile_y][tile_x] != 1)
        cub3d->player.cy = y;
}


void	go_forward(t_cub3d *cub3d)
{
	check_collision_x(cub3d, cub3d->player.cx + cosf(deg_to_rad(cub3d->player.degrees)));
	check_collision_y(cub3d, cub3d->player.cy - sinf(deg_to_rad(cub3d->player.degrees)));
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	cub3d->player.dx = cub3d->player.cx - (cub3d->player.x * PIXELS);
	cub3d->player.dy = cub3d->player.cy - (cub3d->player.y * PIXELS);
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}


void	go_backward(t_cub3d *cub3d)
{
	check_collision_x(cub3d, cub3d->player.cx - cosf(deg_to_rad(cub3d->player.degrees)));
	check_collision_y(cub3d, cub3d->player.cy + sinf(deg_to_rad(cub3d->player.degrees)));
	cub3d->player.dx = (int)cub3d->player.cx % PIXELS;
	cub3d->player.x = (int)cub3d->player.cx / PIXELS;

	cub3d->player.dy = (int)cub3d->player.cy % PIXELS;
	cub3d->player.y = (int)cub3d->player.cy / PIXELS;
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	turn_right(t_cub3d *cub3d)
{
	cub3d->player.degrees += 10;
	if (cub3d->player.degrees >= 360)
		cub3d->player.degrees -= 360;
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

void	turn_left(t_cub3d *cub3d)
{
	cub3d->player.degrees -= 10;
	if (cub3d->player.degrees < 0)
		cub3d->player.degrees += 360;
	mlx_clear_window(cub3d->display.mlx, cub3d->display.mlx_win);
	print_floor(cub3d);
	print_ceiling(cub3d);
	cast_rays(cub3d);
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->display.mlx, cub3d->display.mlx_win, cub3d->img.img, 0, 0);
}

