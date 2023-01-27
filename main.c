#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	// parse all the data needed
	cub3d = parse(argv[1]);
	

	// mlx hook and displaying window
	display_window(cub3d);
	mlx_key_hook(cub3d->display.mlx_win, key_hook, &cub3d);
	mlx_hook(cub3d->display.mlx_win, 17, 0, close_x, &cub3d);
	mlx_loop(cub3d->display.mlx);

	// free cub3d->map.worldMap and close all the fds in cub3d and cub3d->map and exit()

}
