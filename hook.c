/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marie-soleiljarry <marie-soleiljarry@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:28:14 by gvial             #+#    #+#             */
/*   Updated: 2023/02/22 14:52:07 by marie-solei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_x(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->display.mlx, cub3d->display.mlx_win);
	exit(0);
}

int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		go_forward(cub3d);
	if (keycode == 1)
		go_backward(cub3d);
	if (keycode == 0)
		turn_left(cub3d);
	if (keycode == 2)
		turn_right(cub3d);
	print_minimap(cub3d);
	return (0);
}
