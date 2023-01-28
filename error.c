#include "cub3d.h"

// functions which exits in case of color error
void	color_error(t_cub3d *cub3d)
{
	printf("there was a problem getting the floor and/or ceiling color\n");
	error_exit(cub3d);
}

// functions which exits in case of a texture error
void	texture_error(t_cub3d *cub3d)
{
	printf("there was a problem loading the texture\n");
	error_exit(cub3d);
}

// functions which exits in case of an error in the map file
void	arg_error(t_cub3d *cub3d)
{
	printf("arguement invalid\n");
	error_exit(cub3d);
}

// function that will be called at the end of each error msg functions to free and close fds
void	error_exit(t_cub3d *cub3d)
{
	// free stuff

	// close fds

	exit(1);
}