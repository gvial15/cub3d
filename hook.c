#include "cub3d.h"

int	close_x(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->display.mlx, cub3d->display.mlx_win);
	exit(0);
}

int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == 53)
		exit(0); // will need a better exit function to free and close the needed stuff
	if (keycode == 13)
		dprintf(2, "w\n");
		// go_forward(cub3d);
	if (keycode == 1)
		dprintf(2, "s\n");
		// go_backward(cub3d);
	if (keycode == 0)
		dprintf(2, "a\n");
	if (keycode == 2)
		dprintf(2, "d\n");
	print_minimap(cub3d);
	return (0);
}
