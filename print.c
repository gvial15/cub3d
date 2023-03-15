#include "cub3d.h"

void	print_info(t_cub3d *cub3d) // temp function to know what values we have init in our struct
{
	dprintf(2, "texture dimensions?: \nx: %d\ny: %d\n", cub3d->display.img_height, cub3d->display.img_width);
	dprintf(2, "map dimensions: \nx: %d\ny: %d\n", cub3d->map.height, cub3d->map.width);
	dprintf(2, "player position: \nx: %d\ny: %d\n", cub3d->player.x, cub3d->player.y);
	dprintf(2, "total player position: \ncx: %f\ncy: %f\n", cub3d->player.cx, cub3d->player.cy);
	dprintf(2, "player angle: %f\n", cub3d->player.degrees);
	// while (*cub3d->map.map)
	// 	dprintf(2, "map content: %d\n", **(cub3d->map.map++));
}

void	put_cube(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= PIXELS)
	{
		j = 0;
		while (j <= PIXELS)
		{
			if (i % PIXELS != 0 || j % PIXELS != 0)
				my_mlx_pixel_put(&cub3d->img, ((y * PIXELS) + i), ((x * PIXELS) + j), color);
			if (i % PIXELS == 0 || j % PIXELS == 0)
				my_mlx_pixel_put(&cub3d->img, ((y * PIXELS) + i), ((x * PIXELS) + j), 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	print_player(t_cub3d *cub3d, int cx, int cy)
{
	int	i;
	int	j;
	int	size;

	size = 2;
	i = cx - size;
	while (i < cx + size)
	{
		j = cy - size;
		while (j < cy + size)
		{
			my_mlx_pixel_put(&cub3d->img, i, j, 0x0000FF);
			// mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, \
			// i, j, 0x0000FF);
			j++;
		}
		i++;
	}
}

void	print_minimap(t_cub3d *cub3d)
{
	int	x;
	int	y;

	print_info(cub3d);
	x = 0;
	while (x < cub3d->map.height)
	{
		y = 0;
		while (y < cub3d->map.width)
		{
			if (cub3d->map.map[x][y] == 1)
				put_cube(cub3d, x, y, 0);
			else if (cub3d->map.map[x][y] >= 0)
				put_cube(cub3d, x, y, 0x0199120);
			y++;
		}
		x++;
	}
	print_player(cub3d, cub3d->player.cx, cub3d->player.cy);
}
