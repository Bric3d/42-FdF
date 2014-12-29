/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movenscale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:19:44 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/16 17:24:49 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (kc == 65360 && env->pxsize < env->p - 1)
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

void	ft_displaysize(t_env *env)
{
	int	max;

	if (env->nfo->maxcol > env->nfo->linenu)
		max = env->nfo->maxcol;
	else
		max = env->nfo->linenu;
	env->p = 1000 / max;
	env->x = ft_calcx(env, env->nfo->linenu, 0);
	env->y = env->p;
	env->cu = 0.2;
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
