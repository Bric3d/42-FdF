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

void	ft_initseg(t_env *env, int x, int y, t_lnu *lnu)
{
	int		**tab;
	int		p;
	t_pts	*pts;
	double	cu;
	double	cu2;

	cu = env->cu;
	cu2 = cu / 2;
	p = env->p;
	tab = env->nfo->tab;
	if (x > 0)
	{
		pts = ft_putxy((x + tab[y][x] * cu) * p, (y - tab[y][x] * cu2) * p,
			(x - 1 + tab[y][x - 1] * cu) * p, (y - tab[y][x - 1] * cu2) * p);
		ft_bresenham(env, pts, (tab[y][x] + tab[y][x - 1]) * 0.5);
		free(pts);
	}
	if (y > 0 && x < lnu->prv->llin)
	{
		pts = ft_putxy((x + tab[y][x] * cu) * p, (y - tab[y][x] * cu2) * p,
			(x + tab[y - 1][x] * cu) * p, (y - 1 - tab[y - 1][x] * cu2) * p);
		ft_bresenham(env, pts, (tab[y][x] + tab[y - 1][x]) * 0.5);
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
