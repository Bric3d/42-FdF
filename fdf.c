/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:11:59 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/03 19:59:19 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	ft_error(char *str, char *str2)
{
	ft_putstr_fd("FdF : ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	perror(str2);
}

int		ft_openfile(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_error(str, "Open");
		exit(-1);
	}
	return (fd);
}

int		ft_count_line(t_line *line)
{
	int i;

	i = 0;
	if (line)
	{
		while (line && line->line)
		{
			i++;
			line = line->nxt;
		}
	}
	return (i);
}

t_line	*ft_create_elem()
{
	t_line	*line;

	line = NULL;
	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
	{
		ft_error(NULL ,"Malloc");
		exit(-1);
	}
	line->nxt = NULL;
	line->line = NULL;
	return (line);
}

t_lnu	*ft_create_lnu()
{
	t_lnu	*new;
	new = (t_lnu *)malloc(sizeof(t_lnu));
	new->nxt = NULL;
	new->nxt = NULL;
	new->nu = 0;
	new->end = 0;
	return (new);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int		*ft_strsplitnstuff(t_lnu *lnu, t_line *line)
{
	char	**tab;
	int		*mapline;
	int		i;

	i = 0;
	tab = ft_strsplit(line->line, ' ');
	lnu->end = ft_tablen(tab);
	mapline = (int *)malloc(sizeof(int) * lnu->end);
	if (!tab || !mapline)
	{
		ft_error(NULL, "Malloc");
		exit (-1);
	}
	while (tab[i++])
		mapline[i] = ft_atoi(tab[i]);
	return (mapline);
}

t_lnu	*ft_createlnulist(int n)
{
	int		i;
	t_lnu	*list;
	t_lnu	*fst;

	i = 0;
	list = ft_create_lnu();
	fst = list;
	while (i < n)
	{
		list->fst = fst;
		list->nu = i;
		if (i < n - 1)
		{
			list->nxt = ft_create_lnu();
			list = list->nxt;
		}
		i++;
	}
	return (list->fst);
}

t_nfo	*ft_convertmap(t_line *line)
{
	int		i;
	int		**tab;
	t_lnu	*lnu;
	int		c;
	t_nfo	*nfo;

	c = 0;
	i = ft_count_line(line);
	nfo = (t_nfo *)malloc(sizeof(t_nfo));
	tab = (int **)malloc(sizeof(int *) * i);
	if (!tab || !nfo)
		ft_error(NULL , "Malloc");
	if (!tab || !nfo)
		exit (-1);
	lnu = ft_createlnulist(i);
	while (line && line->line)
	{
		tab[c++] = ft_strsplitnstuff(lnu, line);
		lnu = lnu->nxt;
		line = line->nxt;
	}
	nfo->tab = tab;
	if (!lnu)
		ft_putendl("Damn");
	nfo->lnu = lnu->fst;
	return (nfo);
}

void	ft_read_file(int fd)
{
	char	*str;
	t_line	*line;
	t_line	*first;

	line = ft_create_elem();
	str = NULL;
	first = line;
	line->first = line;
	while (get_next_line(fd, &str) > 0)
	{
		line->line = str;
		line->nxt = ft_create_elem();
		line = line->nxt;
		line->first = first;
	}
	ft_convertmap(line->first);
}

int		main(int argc, char **argv)
{
	int fd;
//	int **tab;

	if (argc > 1)
	{
		if (ft_checkextension(argv[1], ".fdf") != 1)
			ft_putendl_fd("Invalid file type, please use a .fdf map", 2);
		else
		{
			fd = ft_openfile(argv[1]);
			ft_read_file(fd);
		}
	}
	return (0);
}
