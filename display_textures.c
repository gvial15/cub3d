/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:31:41 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:31:42 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display_texture(int orientation, t_rays *ray)
{
	int	color;
	int	index;

	index = ray->wall[0] - ((int)(ray->wall[0] / PIXELS) * PIXELS);

	printf("%i\n", index);

	return (color);
}