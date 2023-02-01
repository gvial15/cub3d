#include "cub3d.h"

void	print_info(t_cub3d *cub3d) // temp function to know what values we have init in our struct
{
	dprintf(2, "texture dimensions?: \nx: %d\ny: %d\n", cub3d->display.img_height, cub3d->display.img_width);
	dprintf(2, "map dimensions: \nx: %d\ny: %d\n", cub3d->map.height, cub3d->map.width);
	dprintf(2, "player position: \nx: %d\ny: %d\n", cub3d->player.x, cub3d->player.y);
	// dprintf(2, "player orientation: %c\n", cub3d->player.orientation);
	// while (*cub3d->map.map)
	// 	dprintf(2, "map content: %d\n", **(cub3d->map.map++));
}

void	put_cube(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;
	int pixels;

	i = 0;
	pixels = 12;
	while (i <= pixels) //# pixels
	{
		j = 0;
		while (j <= pixels)
		{
			if (i % pixels != 0 || j % pixels != 0)
				mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, ((y * pixels) + i), ((x * pixels) + j), color);
			if (i % pixels == 0 || j % pixels == 0)
				mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, ((y * pixels) + i), ((x * pixels) + j), 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	print_player(t_cub3d *cub3d, int x, int y)
{
	int pixel;
	int i;
	int j;
	int dx;
	int	dy;

	pixel = cub3d->display.pixels;
	dx = cub3d->player.dx;
	dy = cub3d->player.dy;
	i = dx - 2;
	//to remove :
	x = 3;
	y = 6;

	while (i <= dx + 2)
	{
		j = dy - 2;
		while (j <= dy + 2)
		{
			mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, (y * pixel) + dy, (x * pixel) + dx, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	print_minimap(t_cub3d *cub3d)
{
	int	x;
	int y;
	int tmap[11][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, -1, -1, -1, -1, 1, 1, -1}
	};

	x = 0;
	while (x < 11) // mapsize x / maxwidth?
	{
		y = 0;
		while (y < 10) // mapsize y / maxlength?
		{
			if (tmap[x][y] == 1)
				put_cube(cub3d, x, y, 0);	//black
			else if (tmap[x][y] == 0)
				put_cube(cub3d, x, y, 0x0199120);  //green
			y++;
		}
		x++;
	}
	print_player(cub3d, cub3d->player.x, cub3d->player.y);
}
