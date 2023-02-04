#include "cub3d.h"
#include "lib/libft/libft.h"

// functions which exits in case of color error
void	color_error()
{
	printf("there was a problem getting the floor and/or ceiling color\n");
	exit(1);
}

// functions which exits in case of a texture error
void	texture_error()
{
	printf("there was a problem loading the textures\n");
	exit(1);
}

// functions which exits in case of an error in the map file
void	arg_error()
{
	printf("arguement invalid\n");
	exit(1);
}

void	player_error(char *map)
{
	printf("player error\n");
	free(map);
	exit(1);
}

void	map_error(t_cub3d *cub3d, char *map)
{
	printf("the map doesn't conform with the requirement\n");
	if (cub3d->map.map)
		free_split((void**)cub3d->map.map, cub3d->map.height);
	if (!map)
		free(map);
	exit(1);
}
