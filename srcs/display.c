/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:40:52 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/15 16:40:54 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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

void	ft_putpxl(t_env *env, double x, double y, int color)
{
	int	z;
	int	w;
	int	xa;
	int	ya;

	ya = env->y + y;
	xa = env->x + x;
	z = 0;
	if (ya <= env->size && xa <= env->size && ya >= 0 && xa >= 0)
	{
		while (z < env->pxsize)
		{
			w = 0;
			while (w < env->pxsize)
			{
				mlx_pixel_put(env->init, env->win, w + xa, z + ya, color);
				w++;
			}
			z++;
		}
	}
}

t_pts	*ft_putxy(double x1, double y1, double x2, double y2)
{
	t_pts	*pts;

	pts = (t_pts *)malloc(sizeof(t_pts));
	pts->x1 = x1;
	pts->y1 = y1;
	pts->x2 = x2;
	pts->y2 = y2;
	return (pts);
}

void	ft_filla(t_pts *pts, double *a)
{
	a[0] = ft_abs(pts->x2 - pts->x1);
	a[1] = pts->x1 < pts->x2 ? 1 : -1;
	a[2] = ft_abs(pts->y2 - pts->y1);
	a[3] = pts->y1 < (pts->y2) ? 1 : -1;
	a[4] = (a[0] > a[2] ? a[0] : -a[2]) * 0.5;
}

int		ft_checkwin(t_env *env, t_pts *pts)
{
	int	ya;
	int	xa;
	int	size;

	ya = env->y;
	xa = env->x;
	size = env->size;
	if (pts->x1 + xa > size && pts->y1 + ya > size
			&& pts->x2 + xa > size && pts->y2 + ya > size)
		return (0);
	else if (pts->x1 + xa <= 0 && pts->y1 + ya <= 0
			&& pts->x2 + xa <= 0 && pts->y2 + ya <= 0)
		return (0);
	else
		return (1);
}

void	ft_bresenham(t_env *env, t_pts *pts, int height)
{
	double	a[5];
	double	e2;
	int		state;

	state = 1;
	ft_filla(pts, a);
	while (state == 1 && ft_checkwin(env, pts) == 1
		&& !((int)pts->x1 == (int)pts->x2 && (int)pts->y1 == (int)pts->y2))
	{
		ft_putpxl(env, pts->x1, pts->y1, ft_color(height));
		e2 = a[4];
		state = 0;
		if (e2 > (-a[0]) && (int)pts->x1 != (int)pts->x2)
		{
			a[4] -= a[2];
			pts->x1 += a[1];
			state = 1;
		}
		if (e2 < a[2] && (int)pts->y1 != (int)pts->y2)
		{
			a[4] += a[0];
			pts->y1 += a[3];
			state = 1;
		}
	}
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
	lnu = (void *)lnu;
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

void	ft_displaysize(t_env *env)
{
	int	max;

	if (env->nfo->maxcol > env->nfo->linenu)
		max = env->nfo->maxcol;
	else
		max = env->nfo->linenu;
	env->p = 1000 / max;
	env->x = env->p;
	env->y = env->p;
	env->cu = 0.05;
	env->size = 1100;
	env->pxsize = 1;
}

void	ft_replay(t_env *env)
{
	mlx_clear_window(env->init, env->win);
	ft_printpixels(env);
}

void	ft_move(t_env *env, int kc)
{
	if (kc == 65362)
		env->y = env->y + env->p;
	if (kc == 65364)
		env->y = env->y - env->p;
	if (kc == 65361)
		env->x = env->x + env->p;
	if (kc == 65363)
		env->x = env->x - env->p;
}

void	ft_exit(t_env *env)
{
	t_lnu	*lnu;
	t_lnu	*tmp;
	int		i;

	i = 0;
	lnu = env->nfo->lnu->fst;
	while (lnu)
	{
		tmp = lnu->nxt;
		free(lnu);
		lnu = tmp;
	}
	while (i < env->nfo->linenu)
		free(env->nfo->tab[i++]);
	free(env->nfo->tab);
	free(env->nfo);
	free(env);
	exit (0);
}

void	ft_zoomnscale(t_env *env, int kc)
{
	if (kc == 45 || kc == 65453)
		env->p--;
	if (kc == 61 || kc == 65451)
		env->p++;
	if (kc == 65365)
		env->cu = env->cu + 0.001;
	if (kc == 65366)
		env->cu = env->cu - 0.001;
	if (kc == 65360)
		env->pxsize++;
}

int		ft_key_hook(int kc, t_env *env)
{
	if (kc == 65307)
		ft_exit (env);
	if (kc == 45 || kc == 65453 || kc == 61 || kc == 65451 || kc == 65362
			|| kc == 65364 || kc == 65361 || kc == 65363 || kc == 65365
			|| kc == 65366 || kc == 65360 || kc == 65367 || kc == 114)
	{
		if (kc == 114)
			ft_displaysize(env);
		if (kc == 65367 && env->pxsize == 1)
			return (0);
		if (kc == 65367)
			env->pxsize--;
		ft_move(env, kc);
		ft_zoomnscale(env, kc);
		ft_replay(env);
	}
	return (0);
}

void	display(t_nfo *nfo)
{
	t_env   *env;

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
