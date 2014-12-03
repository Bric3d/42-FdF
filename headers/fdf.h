/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:13:14 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/03 18:40:44 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>


typedef struct	s_lnu
{
	struct s_lnu	*nxt;
	struct s_lnu	*fst;
	int				nu;
	int				end;
}				t_lnu;

typedef struct	s_line
{
	struct s_line	*nxt;
	struct s_line	*first;
	char			*line;
}				t_line;

typedef struct	s_nfo
{
	int		**tab;
	t_lnu	*lnu;
}				t_nfo;

typedef struct	s_env
{
	void	*init;
	void	*win;
	int		x;
	int		y;
	int		z;
}				t_env;

#endif
