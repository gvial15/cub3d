/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:25:29 by gvial             #+#    #+#             */
/*   Updated: 2023/03/22 14:09:24 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1980 //WINDOW WIDTH
# define HEIGHT 1080 //WINDOW HEIGHT
# define PIXELS 20 //NUMBER OF PIXELS PER SQUARE
#define FOV 60
#define NUM_RAYS 1200

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
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
	float		rad;
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_display {
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
}	t_display;


typedef struct s_rays {
	float	angle;
	float	x;
	float	y;
	float	wall[2];
	float	h_check[2];
	float	v_check[2];
	float	dist;
	int		id;
	int		h_wall_found;
	int		v_wall_found;
}	t_rays;

typedef struct s_texture {
	int	**texture;
	int	*colors;
	int	height;
	int	width;
}	t_texture;

typedef struct s_cub3d {
	char		*map_path;
	int			map_fd;
	int			norm_bs;
	float		ang_incr;
	t_data		img;
	t_data		tmp;
	t_map		map;
	t_player	player;
	t_display	display;
	t_rays		*rays;
	t_texture	textures[4];
}	t_cub3d;

// parsing
int		get_index(char *line);
int		nb_color(char **file);
void	parse(t_cub3d *cub3d);
void	log_map(t_cub3d *cub3d);
void	free_map(t_cub3d *cub3d);
char	*fill_map(t_cub3d *cub3d);
void	alloc_map(t_cub3d *cub3d);
void	parse_map(t_cub3d *cub3d);
void	get_colors(t_cub3d *cub3d);
void	parse_texture(t_cub3d *cub3d);
void	free_textures(t_cub3d *cub3d);
void	set_orientation(t_cub3d *cub3d, char c);
void	get_texture_colors(t_texture *texture, char **file);

// displaying
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		display_texture(int orientation, t_rays *ray);
void	display_window(t_cub3d *cub3d);
void	print_ceiling(t_cub3d *cub3d);
void	print_floor(t_cub3d *cub3d);
int		rgb_to_int(int *color);

// printing initial position
void	print_minimap(t_cub3d *cub3d);

// mlx hook
int		close_x(t_cub3d *cub3d);
int		key_hook(int keycode, t_cub3d *cub3d);

//movement
void	go_forward(t_cub3d *cub3d);
void	go_backward(t_cub3d *cub3d);
void	turn_left(t_cub3d *cub3d);
void	turn_right(t_cub3d *cub3d);
float	deg_to_rad(float degrees);

//raycasting
void	create_rays(t_cub3d *cub3d);
void	cast_rays(t_cub3d *cub3d);

// error
void	arg_error(void);
void	color_error(void);
void	map_error(t_cub3d *cub3d);
void	player_error(t_cub3d *cub3d);
void	texture_error(char *line, char **file);

//temp
void	print_info(t_cub3d *cub3d);
void	draw_line(t_cub3d *cub3d, float x1, float y1, float x2, float y2);

#endif
