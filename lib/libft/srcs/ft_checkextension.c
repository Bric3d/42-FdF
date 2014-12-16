/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkextension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:35:00 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/16 17:28:19 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkextension(char *name, char *extension)
{
	int i;
	int x;

	if (name && extension)
	{
		i = ft_strlen(name) - 1;
		x = ft_strlen(extension) - 1;
		if (i < x || x <= 0 || i <= 0)
			return (0);
		while (x >= 0)
			if (name[i--] != extension[x--])
				return (0);
		return (1);
	}
	return (0);
}
