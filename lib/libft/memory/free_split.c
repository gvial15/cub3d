/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:32:58 by gvial             #+#    #+#             */
/*   Updated: 2022/08/01 20:33:52 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_split(void **split, int split_length)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (++i < split_length)
		free(split[i]);
	free(split);
}
