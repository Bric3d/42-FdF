/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initseg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 11:59:00 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/09 11:59:22 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_calcx(t_env *env, int x, int y)
{
	int	p;

	p = env->p;
	return ((x - y) * p);
}

double	ft_calcy(t_env *env, int x, int y)
{
	int		**tab;
	double	p;
	double	cu;

	cu = env->cu;
	p = env->p * 0.5;
	tab = env->nfo->tab;
	return ((x + y - tab[y][x] * cu) * p);
}

void	ft_initseg(t_env *e, int x, int y, t_lnu *lnu)
{
	int		**tab;
	t_pts	*pts;

	tab = e->nfo->tab;
	if (x > 0)
	{
		pts = ft_putxy(ft_calcx(e, x, y), ft_calcy(e, x, y),
				ft_calcx(e, x - 1, y), ft_calcy(e, x - 1, y));
		ft_bresenham(e, pts, (tab[y][x] + tab[y][x - 1]) * 0.5);
		free(pts);
	}
	if (y > 0 && x < lnu->prv->llin)
	{
		pts = ft_putxy(ft_calcx(e, x, y), ft_calcy(e, x, y),
				ft_calcx(e, x, y - 1), ft_calcy(e, x, y - 1));
		ft_bresenham(e, pts, (tab[y][x] + tab[y - 1][x]) * 0.5);
		free(pts);
	}
}
