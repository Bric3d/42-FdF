/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:13:34 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/08 14:27:25 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_line(int *line, int ymax)
{
	int y;

	y = 0;
	while (y < ymax)
	{
		ft_putnbr(line[y]);
		if (line[y] == 0)
			ft_putchar(' ');
		ft_putchar(' ');
		y++;
	}
}

void	ft_printinttab(t_nfo *nfo)
{
	t_lnu	*lnu;
	int		**tab;
	int		x;

	x = 0;
	tab = nfo->tab;
	lnu = nfo->lnu;
	while (x < nfo->linenu)
	{
		ft_print_line(tab[x], lnu->llin);
		if (lnu->nxt)
			lnu = lnu->nxt;
		x++;
		ft_putchar('\n');
	}
}
