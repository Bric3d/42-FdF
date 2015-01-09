/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:40:52 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/09 14:02:28 by bbecker          ###   ########.fr       */
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
	env->win = mlx_new_window(env->init, env->sizex, env->sizey, nfo->name);
	mlx_hook(env->win, 1, 3, ft_key_hook, env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_printpixels, env);
	mlx_loop(env->init);
}
