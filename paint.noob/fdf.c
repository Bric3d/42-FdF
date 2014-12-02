/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 18:29:38 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/02 20:18:53 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

int	ft_expose_hook(t_env *env)
{
	mlx_pixel_put(env->init, env->win, env->x / 2, env->y / 2, 0x7F4545);
	mlx_pixel_put(env->init, env->win, (env->x / 2) + 1, env->y / 2, 0x7F4545);
	mlx_pixel_put(env->init, env->win, env->x / 2, (env->y / 2) + 1, 0x7F4545);
	mlx_pixel_put(env->init, env->win, (env->x / 2) + 1, (env->y / 2) + 1, 0x7F4545);
	return (0);
}

int	ft_key_hook(int keycode, t_env *env)
{
	env = (t_env *)env;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
		exit (0);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_env *env)
{
	int x2;
	int y2;

	x2 = x;
	y2 = y;
	y = y - 25;
	while (y++ <= y2 + 25)
	{
		x = x2 - 25;
		while (x++ <= x2 + 25)
			mlx_pixel_put(env->init, env->win, x, y, 0x7F4545);
	}
	ft_putstr("Button : ");
	ft_putnbr(button);
	ft_putchar('\n');
	ft_putstr(" x, y ; ");
	ft_putnbr(x);
	ft_putstr(", ");
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}


int	ft_mlxstuff(int x, int y)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->init = mlx_init();
	env->win = mlx_new_window(env->init, x, y, "Paint.noob");
	env->x = x;
	env->y = y;
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_mouse_hook(env->win, ft_mouse_hook, env);
	mlx_expose_hook(env->win, ft_expose_hook, env);
	mlx_loop(env->init);
	return (0);
}

int	main(int ac, char **av)
{
	int	x;
	int	y;

	x = 100;
	y = 100;
	if (ac == 3)
	{
		x = ft_atoi(av[1]);
		y = ft_atoi(av[2]);
	}
	ft_mlxstuff(x, y);
	return (0);
}
