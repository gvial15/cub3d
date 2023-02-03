#include "cub3d.h"

void	alloc_map(t_cub3d *cub3d, char *map)
{
	int		i;
	int		x;
	int		y;
	char	**split;

	split = ft_split(map, '\n');
	y = split_len(split);
	x = 0;
	i = -1;
	while (split[++i])
		if (ft_strlen(split[i]) > x)
			x = ft_strlen(split[i]);
	cub3d->map.map = malloc(sizeof(int *) * y);
	i = y;
	while (--i >= 0)
		cub3d->map.map[i] = ft_calloc(x, sizeof(int));
	cub3d->map.height = y;
	cub3d->map.width = x;
	free_split((void**)split, split_len(split));
}

void	log_map(t_cub3d *cub3d, char *map)
{
	int		i;
	int		x;
	int		z;
	char	**split;

	split = ft_split(map, '\n');
	i = -1;
	z = 0;
	x = -1;
	while (split[++i])
	{
		while (++x < cub3d->map.width)
		{
			if (split[i][z] && split[i][z] != ' ')
				cub3d->map.map[i][x] = split[i][z] - 48;
			else
				cub3d->map.map[i][x] = -1;
			z++;
		}
		x = -1;
		z = 0;
	}
}
