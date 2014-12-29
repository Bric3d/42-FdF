/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:40:52 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/16 17:24:32 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

int		ft_color(int z)
{
	if (z <= 0)
		return (0x0000ff);
	if (z > 0 && z < 10)
		return (0xF7DF7D);
	if (z > 9 && z < 60)
		return (0x21B84E);
	if (z > 59 && z < 100)
		return (0x21B84E);
	if (z > 99 && z < 160)
		return (0x855C48);
	else
		return (0xffffff);
}

double	ft_calcx(t_env *env, int x, int y)
{
	int	p;

	p = env->p;
	return ((x - y) * p);
}

double	ft_calcy(t_env *env, int x, int y)
{
	int		**tab;
	int		p;
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

int		ft_printpixels(t_env *env)
{
	t_lnu	*lnu;
	int		x;
	int		y;

	y = 0;
	lnu = env->nfo->lnu;
	while (y < env->nfo->linenu)
	{
		x = 0;
		while (x < lnu->llin)
		{
			ft_initseg(env, x, y, lnu);
			x++;
		}
		y++;
		if (lnu->nxt)
			lnu = lnu->nxt;
	}
	return (0);
}

void	display(t_nfo *nfo)
{
	t_env	*env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		ft_error(NULL, "Malloc");
	env->nfo = nfo;
	env->init = mlx_init();
	ft_displaysize(env);
	env->win = mlx_new_window(env->init, env->size, env->size, "FdF");
	mlx_hook(env->win, 1, 3, ft_key_hook, env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_printpixels, env);
	mlx_loop(env->init);
}
