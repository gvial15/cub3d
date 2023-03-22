/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:35:17 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:35:18 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// use this whenever exiting the program
void	free_textures(t_cub3d *cub3d)
{
	int	i;
	int	len;

	i = -1;
	while (++i < 4)
	{
		len = split_len(cub3d->textures[i].texture);
		free_split((void **)cub3d->textures[i].texture, len);
		free(cub3d->textures->colors);
	}
}

int	nb_color(char **file)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (file[++i][0] != '"' && !ft_isdigit(file[i][1]));
	while (!ft_strnstr(file[i++], "/* pixels */", 12))
		n++;
	return (n - 1);
}

void	parse_color(t_cub3d *cub3d, char *line, int index, int ii)
{
	char	**split;
	int		color;
	char	*tmp;
	
	split = ft_split(line, ' ');
	if (ft_strlen(split[0]) == 1)
	{
		tmp = ft_strdup(" ");
		cub3d->textures[index].colors[ii] = tmp[0];
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(split[0], "\"\n");
		cub3d->textures[index].colors[ii] = tmp[0];
		free(tmp);
	}
	tmp = ft_strtrim(split[2], "#\"\n,");
	color = ft_atoi_base(tmp, 16);
	free(tmp);
	cub3d->textures[index].colors[ii + 1] = color;
	free_split((void **)split, split_len(split));
}

void	get_texture_colors(t_cub3d *cub3d, int index, char **file)
{
	int	i;
	int	ii;

	cub3d->textures[index].colors = ft_calloc((nb_color(file) * 2) + 1, sizeof(int));
	ii = 0;
	i = -1;
	while (file[++i][0] != '"' && !ft_isdigit(file[i][1]));
	while (!ft_strnstr(file[++i], "/* pixels */", 12))
	{
		parse_color(cub3d, file[i], index, ii);
		ii += 2;
	}
}
