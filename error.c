/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:22:13 by gvial             #+#    #+#             */
/*   Updated: 2023/04/17 13:50:16 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// functions which exits in case of color error
void	color_error(char **split)
{
	if (split)
		free_split((void **)split, split_len((void **)split));
	printf("there was a problem getting the floor and/or ceiling color\n");
	exit(1);
}

// functions which exits in case of a texture error
void	texture_error(char *line, char **file)
{
	printf("there was a problem loading the textures\n");
	if (line)
		free(line);
	if (file)
		free_split((void **)file, split_len((void **)file));
	exit(1);
}

// functions which exits in case of an error in the argument (path)
void	arg_error(void)
{
	printf("arguement invalid\n");
	exit(1);
}

// functions which exits in case of an error in the map regarding the player
void	player_error(t_cub3d *cub3d)
{
	printf("player error\n");
	if (cub3d->map.map_c)
		free(cub3d->map.map_c);
	if (cub3d->map.map_d)
		free_split((void **)cub3d->map.map_d, split_len((void **)cub3d->map.map_d));
	exit(1);
}

// functions which exits in case of an error in the map
void	map_error(t_cub3d *cub3d)
{
	printf("the map doesn't conform with the requirement\n");
	if (cub3d->map.map)
		free_split((void **)cub3d->map.map, cub3d->map.height);
	if (cub3d->map.map_c)
		free(cub3d->map.map_c);
	if (cub3d->map.map_d)
		free_split((void **)cub3d->map.map_d, \
			split_len((void **)cub3d->map.map_d));
	exit(1);
}
