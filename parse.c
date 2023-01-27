#include "cub3d.h"

// function for testing related to testing
void	parsing_test(t_cub3d *cub3d)
{
	printf("cub3d->mapfd: %i\n", cub3d->mapfd);
}

// parsing the texture in the .cub file and saving their pointer to cub3d->map.<n/s/e/w>_fd
void	parse_texture(t_cub3d *cub3d)
{
	
}

t_cub3d	*parse(char *arg)
{
	t_cub3d	*cub3d;

	if (!arg)
		arg_error(cub3d, 0);
	cub3d = malloc(sizeof(t_cub3d));
	cub3d->mapfd = open(arg, O_RDONLY);

	// parsing_test(cub3d);

	parse_texture(cub3d);
	// todo: parse ceilling and floor color into cub3d->map.<f/c>_color[3];

	// todo: parse the map into an int**

	close(cub3d->mapfd);
	return (cub3d);
}
