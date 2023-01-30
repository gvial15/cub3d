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
	int	**worldMap;
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
void	parse_texture(t_cub3d *cub3d);
void	get_colors(t_cub3d *cub3d);

// displaying
void	display_window(t_cub3d *cub3d);

// mlx hook
int		close_x(t_cub3d *cub3d);
int		key_hook(int keycode, t_cub3d *cub3d);

// error
void	arg_error(t_cub3d *cub3d);
void	error_exit(t_cub3d *cub3d);
void	color_error(t_cub3d *cub3d);
void	texture_error(t_cub3d *cub3d);

#endif
