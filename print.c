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

void	print_minimap(t_cub3d *cub3d)
{
	int	x;
	int y;

	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 400)
		{
			mlx_pixel_put(cub3d->display.mlx, cub3d->display.mlx_win, y, x, 0xB2AC88);
			y++;
		}
		x++;
	}
}
