#include "cub3d.h"

void	parse(t_cub3d *cub3d)
{
	parse_texture(cub3d);
	get_colors(cub3d);
	// todo: parse the map into an int**, player x/y and orientation

}
