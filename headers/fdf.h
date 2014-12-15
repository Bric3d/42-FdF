/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:13:14 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/08 15:45:47 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"

typedef struct	s_lnu
{
	struct s_lnu	*nxt;
	struct s_lnu	*prv;
	struct s_lnu	*fst;
	int				nu;
	int				llin;
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
	int		maxcol;
	int		linenu;
}				t_nfo;

typedef struct 	s_pts
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
}				t_pts;

typedef struct	s_env
{
	void	*init;
	void	*win;
	t_nfo	*nfo;
	int		p;
	int		x;
	int 	y;
	double	cu;
	int		size;
	int		pxsize;
}				t_env;
/*
** error.c
*/
void	ft_error(char *str, char *str2);
/*
** writeintab.c
*/
int		*ft_strsplitnstuff(t_lnu *lnu, t_line *line);
void	ft_write_total(int c, t_lnu *lnu);
int		ft_writeintab(t_line *line, int **tab, t_lnu *lnu, int c);
t_nfo	*ft_makeinttab(t_line *line);
/*
** readfile.c
*/
t_nfo	*ft_read_file(int fd);
int		ft_openfile(char *str);
/*
** printtab.c
*/
void	ft_print_line(int *line, int ymax);
void	ft_printinttab(t_nfo *nfo);
/*
** createelem.c
*/
t_line	*ft_create_elem(void);
t_lnu	*ft_create_lnu(void);
t_lnu	*ft_createlnulist(int n);
void	ft_free_all(t_infos *infos);
void 	freeline(t_line *line);
/*
** cout.c
*/
int		ft_count_line(t_line *line);
int		ft_tablen(char **tab);

void 	display(t_nfo *nfo);

#endif
