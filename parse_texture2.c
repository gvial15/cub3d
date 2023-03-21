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

static int	nb_color(char **file)
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
	
	split = ft_split(line, ' ');
	if (ft_strlen(split[0]) == 1)
		cub3d->textures[index].colors[ii] = ft_strdup(" ");
	else
		cub3d->textures[index].colors[ii] = ft_strtrim(split[0], "\"\n");
	cub3d->textures[index].colors[ii + 1] = ft_strtrim(split[2], "\"\n,");
	free_split((void **)split, split_len(split));
}

void	get_texture_colors(t_cub3d *cub3d, int index, char **file)
{
	int	i;
	int	ii;

	cub3d->textures[index].colors = ft_calloc((nb_color(file) * 2) + 1, sizeof(char *));
	ii = 0;
	i = -1;
	while (file[++i][0] != '"' && !ft_isdigit(file[i][1]));
	while (!ft_strnstr(file[++i], "/* pixels */", 12))
	{
		parse_color(cub3d, file[i], index, ii);
		ii += 2;
	}
}
