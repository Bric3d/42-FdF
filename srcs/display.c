#include "fdf.h"
#include <stdio.h>

int     ft_color(int z)
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


void    ft_putpxl(t_env *env, double x, double y, int color)
{
	int size;
	int z;
	int w;
	int xa;
	int ya;

	ya = env->y;
	xa = env->x;
	size = 2;
	z = 0;

	while (z < size)
	{
		w = 0;
		while (w < size)
		{
			mlx_pixel_put(env->init, env->win, x + w + xa, y + z + ya, color);
			w++;
		}
		z++;
	}
}

t_pts   *ft_putxy(double x1, double y1, double x2, double y2)
{
	t_pts *pts;

	pts = (t_pts *)malloc(sizeof(t_pts));
	pts->x1 = x1;
	pts->y1 = y1;
	pts->x2 = x2;
	pts->y2 = y2;
	return (pts);
}

void    ft_filla(t_pts *pts, double *a)
{
	a[0] = ft_abs(pts->x2 - pts->x1);
	a[1] = pts->x1 < pts->x2 ? 1 : -1;
	a[2] = ft_abs(pts->y2 - pts->y1);
	a[3] = pts->y1 < (pts->y2) ? 1 : -1;
	a[4] = (a[0] > a[2] ? a[0] : -a[2]) * 0.5;
}

void    ft_bresenham(t_env *env, t_pts *pts, int height)
{
	double  a[5];
	double  e2;
	int     state;

	state = 1;
	ft_filla(pts, a);
	while (state == 1)
	{
		ft_putpxl(env, pts->x1, pts->y1, ft_color(height));
		if ((int)pts->x1 == (int)pts->x2 && (int)pts->y1 == (int)pts->y2)
			break ;
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

void    ft_initseg(t_env *env, int x, int y, t_lnu *lnu)
{
	int     **tab;
	int     p;
	t_pts   *pts;

	lnu = (void *)lnu;
	p = env->p;
	tab = env->nfo->tab;
	if (x > 0)
	{
		pts = ft_putxy((x + tab[y][x] * 0.05) * p, (y - tab[y][x] * 0.025) * p,
				(x - 1 + tab[y][x - 1] * 0.05) * p, (y - tab[y][x - 1] * 0.025) * p);
		ft_bresenham(env, pts, (tab[y][x] + tab[y][x - 1]) * 0.5);
		free(pts);
	}
	if (y > 0 && x < lnu->prv->llin)
	{
		pts = ft_putxy((x + tab[y][x] * 0.05) * p, (y - tab[y][x] * 0.025) * p,
				(x + tab[y - 1][x] * 0.05) * p, (y - 1 - tab[y - 1][x] * 0.025) * p);
		ft_bresenham(env, pts, (tab[y][x] + tab[y - 1][x]) * 0.5);
		free(pts);
	}
}

int     ft_printpixels(t_env *env)
{
	t_lnu   *lnu;
	int     x;
	int     y;

	y = 0;
	lnu = env->nfo->lnu;
	while (y < env->nfo->linenu)
	{
		x = 0;
		while(x < lnu->llin)
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

void    ft_displaysize(t_env *env)
{
	int max;

	if (env->nfo->maxcol > env->nfo->linenu)
		max = env->nfo->maxcol;
	else
		max = env->nfo->linenu;
	env->p = 1000 / max;
	env->x = 100;
	env->y = 100;
}

void    ft_replay(t_env *env)
{
	mlx_clear_window(env->init, env->win);
	ft_printpixels(env);
}

void    ft_move(t_env *env, int kc)
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

void 	ft_exit(t_env *env)
{
	t_lnu	*lnu;
	t_lnu	*tmp;
	int		i;

	i = 0;
	lnu = env->nfo->lnu->fst;
	while(lnu)
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

int	    ft_key_hook(int kc, t_env *env)
{
	if (kc == 65307)
		ft_exit (env);
	if (kc == 45 || kc == 65453 || kc == 61 || kc == 65451
			|| kc == 65362 || kc == 65364 || kc == 65361 || kc == 65363)
	{
		if (kc == 45 || kc == 65453)
			env->p--;
		if (kc == 61 || kc == 65451)
			env->p++;
		ft_move(env, kc);
		ft_replay(env);
	}
	return (0);
}

void    display(t_nfo *nfo)
{
	t_env   *env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		ft_error(NULL, "Malloc");
	env->nfo = nfo;
	env->init = mlx_init();
	ft_displaysize(env);
	env->win = mlx_new_window(env->init, 1100, 1100, "FdF");
	mlx_hook(env->win, 1, 3, ft_key_hook, env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_printpixels, env);
	mlx_loop(env->init);
}
