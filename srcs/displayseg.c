/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayseg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:17:06 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/09 11:48:25 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putpxl(t_env *env, int x, int y, int color)
{
	int	z;
	int	w;
	int	xa;
	int	ya;

	ya = env->y + y;
	xa = env->x + x;
	z = 0;
	if (ya <= env->sizey && xa <= env->sizex && ya >= 0 && xa >= 0)
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
	int	sizex;
	int	sizey;

	ya = env->y;
	xa = env->x;
	sizex = env->sizex;
	sizey = env->sizey;
	if (pts->x1 + xa > sizex && pts->y1 + ya > sizey
			&& pts->x2 + xa > sizex && pts->y2 + ya > sizey)
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
		ft_putpxl(env, pts->x1, pts->y1, ft_color(height + env->z));
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
