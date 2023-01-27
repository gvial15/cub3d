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
	int	n_fd;
	int	s_fd;
	int	e_fd;
	int	w_fd;
	int	f_color[3];
	int	c_color[3];
}	t_map;

typedef struct Display
{
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;
}	t_display;

typedef	struct s_cub3d {
	int			mapfd;
	t_map		map;
	t_player	player;
	t_display	display;
}	t_cub3d;

t_cub3d	*parse(char *arg);


// displaying
void	display_window(t_cub3d *cub3d);

// mlx hook
int		close_x(t_cub3d *cub3d);
int		key_hook(int keycode, t_cub3d *cub3d);

// error
void	error_exit(t_cub3d *cub3d);
void	arg_error(t_cub3d *cub3d, int freeMap);

#endif
