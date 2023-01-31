#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "lib/mlx/mlx.h"
# include "lib/libft/libft.h"

typedef	struct s_player {
	int		x;
	int		y;
	char	orientation;
}	t_player;

typedef	struct s_map {
	int	**map;
	int	width;
	int	height;
	int	f_color[3];
	int	c_color[3];
}	t_map;

typedef struct Display
{
	void	*mlx;
	void	*mlx_win;
	void	*n_texture;
	void	*s_texture;
	void	*e_texture;
	void	*w_texture;
	int		img_width;
	int		img_height;
}	t_display;

typedef	struct s_cub3d {
	char		*map_path;
	t_map		map;
	t_player	player;
	t_display	display;
}	t_cub3d;

// parsing
void	parse(t_cub3d *cub3d);
void	parse_map(t_cub3d *cub3d);
void	get_colors(t_cub3d *cub3d);
void	parse_texture(t_cub3d *cub3d);

// displaying
void	display_window(t_cub3d *cub3d);

// mlx hook
int		close_x(t_cub3d *cub3d);
int		key_hook(int keycode, t_cub3d *cub3d);

// error
void	arg_error();
void	error_exit();
void	color_error();
void	texture_error();
void	map_error(char *map);

#endif
