/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writeintab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:21:36 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/10 16:00:36 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_calcolmax(t_lnu *lnu)
{
	int		max;
	t_lnu	*prv;

	lnu = lnu->fst;
	max = 0;
	while (lnu)
	{
		prv = lnu;
		if (lnu->llin > max)
			max = lnu->llin;
		lnu = lnu->nxt;
		if (lnu)
			lnu->prv = prv;
	}
	return (max);
}

t_nfo	*ft_makeinttab(t_line *line)
{
	int		i;
	int		**tab;
	t_lnu	*lnu;
	int		c;
	t_nfo	*nfo;

	c = 0;
	i = ft_count_line(line);
	nfo = (t_nfo *)malloc(sizeof(t_nfo));
	tab = (int **)malloc(sizeof(int *) * i);
	if (!tab || !nfo)
		ft_error(NULL, "Malloc");
	if (!tab || !nfo)
		exit (-1);
	lnu = ft_createlnulist(i);
	nfo->linenu = ft_writeintab(line, tab, lnu, c);
	nfo->maxcol = ft_calcolmax(lnu->fst);
	nfo->tab = tab;
	nfo->lnu = lnu->fst;
	return (nfo);
}

int		ft_writeintab(t_line *line, int **tab, t_lnu *lnu, int c)
{
	while (line && line->line)
	{
		tab[c++] = ft_strsplitnstuff(lnu, line);
		if (lnu->nxt)
			lnu = lnu->nxt;
		if (line->nxt)
			line = line->nxt;
	}
	return (c);
}

int		*ft_strsplitnstuff(t_lnu *lnu, t_line *line)
{
	char	**tab;
	int		*mapline;
	int		i;

	i = 0;
	tab = ft_strsplit(line->line, ' ');
	lnu->llin = ft_tablen(tab);
	mapline = (int *)malloc(sizeof(int) * lnu->llin);
	if (!tab || !mapline)
	{
		ft_error(NULL, "Malloc");
		exit (-1);
	}
	while (tab[i])
	{
		mapline[i] = ft_atoi(tab[i]);
		i++;
	}
	return (mapline);
}
