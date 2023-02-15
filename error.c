/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:22:13 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:22:16 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// functions which exits in case of color error
void	color_error(void)
{
	printf("there was a problem getting the floor and/or ceiling color\n");
	exit(1);
}

// functions which exits in case of a texture error
void	texture_error(void)
{
	printf("there was a problem loading the textures\n");
	exit(1);
}

// functions which exits in case of an error in the argument (path)
void	arg_error(void)
{
	printf("arguement invalid\n");
	exit(1);
}

// functions which exits in case of an error in the map regarding the player
void	player_error(char *map)
{
	printf("player error\n");
	free(map);
	exit(1);
}

// functions which exits in case of an error in the map
void	map_error(t_cub3d *cub3d, char **map_d, char *map)
{
	printf("the map doesn't conform with the requirement\n");
	if (cub3d->map.map)
		free_split((void **)cub3d->map.map, cub3d->map.height);
	if (map)
		free(map);
	if (map_d)
		free_split((void **)map_d, split_len(map_d));
	exit(1);
}
