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
		printf("w");
	if (keycode == 1)
		printf("s");
	if (keycode == 0)
		printf("a");
	if (keycode == 2)
		printf("d");
	return (0);
}
