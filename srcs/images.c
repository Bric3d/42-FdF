/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 18:38:12 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/08 19:45:29 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_to_img(t_env *ret, int x, int y, int color)
{
	int i;

	i = x * 4 + y * ret->size_line;
	ret->pimg[i] = (color & 0xFF);
	ret->pimg[i + 1] = (color & 0xFF00) >> 8;
	ret->pimg[i + 2] = (color & 0xFF0000) >> 16;
}

int		ft_update_img(t_env *ret, int f(t_env *ret))
{
	ret->img = mlx_new_image(ret->init, ret->size, ret->size);
	ret->pimg = mlx_get_data_addr(ret->img, &(ret->bpp),
			&(ret->size_line), &(ret->endian));
	f(ret);
	mlx_put_image_to_window(ret->init, ret->win, ret->img, 0, 0);
	mlx_destroy_image(ret->init, ret->img);
	return (0);
}

int		expose_hook(t_env *e)
{
	ft_update_img(e, ft_printpixels);
	return (0);
}
