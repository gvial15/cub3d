#include "cub3d.h"

void	display_window(t_cub3d *cub3d)
{
	cub3d->display.mlx_win = mlx_new_window(cub3d->display.mlx, 500, 500, "cub3d");
}
