#include "cub3d.h"

void	display_window(t_cub3d *cub3d)
{
	cub3d->display.mlx_win = \
	mlx_new_window(cub3d->display.mlx, 2560, 1395, "Cub3d");
	print_floor(cub3d);
	print_ceiling(cub3d);

	// print_info(cub3d);

	print_minimap(cub3d);
	// print_layout(cub3d);
}

int	rgb_to_int(int *color)
{
	int	r;
	int	g;
	int	b;

	r = color[0];
	g = color[1];
	b = color[2];
	return ((r << 16) + (g << 8) + b);
}

void	print_floor(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	x = 0;
	color = rgb_to_int(cub3d->map.f_color);
	while (x < 1395)
	{
		y = 0;
		while (y < 2560)
		{
			mlx_pixel_put(cub3d->display.mlx, \
			cub3d->display.mlx_win, y, x, color);
			y++;
		}
		x++;
	}
}

void	print_ceiling(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	x = 0;
	color = rgb_to_int(cub3d->map.c_color);
	while (x < 1395 / 2)
	{
		y = 0;
		while (y < 2560)
		{
			mlx_pixel_put(cub3d->display.mlx, \
			cub3d->display.mlx_win, y, x, color);
			y++;
		}
		x++;
	}
}

