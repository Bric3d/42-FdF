/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:25:02 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/08 14:26:27 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_count_line(t_line *line)
{
	int i;

	i = 0;
	if (line)
	{
		while (line && line->line)
		{
			i++;
			line = line->nxt;
		}
	}
	return (i);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
