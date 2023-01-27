#include "cub3d.h"

// functions which frees everything and exits in case of an error in the map file
void	arg_error(t_cub3d *cub3d, int freeMap)
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