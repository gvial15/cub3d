/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marie-soleiljarry <marie-soleiljarry@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:25:29 by gvial             #+#    #+#             */
/*   Updated: 2023/02/09 17:18:44 by marie-solei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1000
# define HEIGHT 700

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "lib/mlx/mlx.h"
# include "lib/libft/libft.h"

typedef struct s_player {
	int			x;
	float		cx;
	float		dx;
	int			y;
	float		cy;
	float		dy;
	char		orientation;
	float		degrees;
}	t_player;

typedef struct s_map {
	int		**map;
	char	*map_c;
	char	**map_d;
	int		f_color[3];
	int		c_color[3];
	int		width;
	int		height;
}	t_map;

typedef struct s_display {
	void	*mlx;
	void	*mlx_win;
	void	*n_texture;
	void	*s_texture;
	void	*e_texture;
	void	*w_texture;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int		pixels;
}	t_display;

typedef struct s_cub3d {
	char		*map_path;
	int			map_fd;
	int			norm_bs;
	t_map		map;
	t_player	player;
	t_display	display;
}	t_cub3d;

// parsing
void	parse(t_cub3d *cub3d);
char	*fill_map(t_cub3d *cub3d);
void	parse_map(t_cub3d *cub3d);
void	get_colors(t_cub3d *cub3d);
int		skip_to_map(t_cub3d *cub3d);
void	parse_texture(t_cub3d *cub3d);
void	log_map(t_cub3d *cub3d);
void	alloc_map(t_cub3d *cub3d);

// displaying
void	display_window(t_cub3d *cub3d);
void	print_ceiling(t_cub3d *cub3d);
void	print_floor(t_cub3d *cub3d);
int		rgb_to_int(int *color);

// printing initial position
void	print_minimap(t_cub3d *cub3d);

// mlx hook
int		close_x(t_cub3d *cub3d);
int		key_hook(int keycode, t_cub3d *cub3d);

// error
void	arg_error(void);
void	color_error(void);
void	texture_error(void);
void	player_error(t_cub3d *cub3d);
void	map_error(t_cub3d *cub3d);

//temp
void	print_info(t_cub3d *cub3d);

#endif
