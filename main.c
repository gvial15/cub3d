#include "cub3d.h"

// function that display all the data from all the structs for debugging
static void	display_data(t_cub3d *cub3d)
{
	printf("map_fd: %i\n", cub3d->map_fd);
	printf("c_color: %i,%i,%i\n", cub3d->map.c_color[0], cub3d->map.c_color[1], cub3d->map.c_color[2]);
	printf("f_color: %i,%i,%i\n", cub3d->map.f_color[0], cub3d->map.f_color[1], cub3d->map.f_color[2]);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	// parse all the data needed
	cub3d = parse(argv[1]);
	display_data(cub3d);

	// mlx hook and displaying window
	display_window(cub3d);
	mlx_key_hook(cub3d->display.mlx_win, key_hook, &cub3d);
	mlx_hook(cub3d->display.mlx_win, 17, 0, close_x, &cub3d);
	mlx_loop(cub3d->display.mlx);

	// free cub3d->map.worldMap and close all the fds in cub3d and cub3d->map and exit()

}
