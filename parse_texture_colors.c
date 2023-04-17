/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarry <mjarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:35:17 by gvial             #+#    #+#             */
/*   Updated: 2023/04/17 14:01:56 by mjarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	nb_color(char **file)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (file[++i][0] != '"' && !ft_isdigit(file[i][1]))
	{
	}
	while (!ft_strnstr(file[i++], "/* pixels */", 12))
		n++;
	return (n - 1);
}

static void	parse_color(t_texture *texture, char *line, int ii)
{
	char	**split;
	int		color;
	char	*tmp;

	split = ft_split(line, ' ');
	if (ft_strlen(split[0]) == 1)
	{
		tmp = ft_strdup(" ");
		texture->colors[ii] = tmp[0];
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(split[0], "\"\n");
		texture->colors[ii] = tmp[0];
		free(tmp);
	}
	tmp = ft_strtrim(split[2], "#\"\n,");
	color = ft_atoi_base(tmp, 16);
	free(tmp);
	texture->colors[ii + 1] = color;
	free_split((void **)split, split_len((void **)split));
}

void	get_texture_colors(t_texture *texture, char **file)
{
	int	i;
	int	ii;

	texture->colors = ft_calloc((nb_color(file) * 2) + 1, sizeof(int));
	ii = 0;
	i = -1;
	while (file[++i][0] != '"' && !ft_isdigit(file[i][1]))
	{
	}
	while (!ft_strnstr(file[++i], "/* pixels */", 12))
	{
		parse_color(texture, file[i], ii);
		ii += 2;
	}
}
