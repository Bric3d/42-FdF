/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:13:44 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/08 14:26:35 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_nfo	*ft_read_file(int fd)
{
	char	*str;
	t_line	*line;
	t_line	*first;
	t_nfo	*nfo;

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
	nfo = ft_makeinttab(line->first);
	freeline(line->first);
	return (nfo);
}

int		ft_openfile(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_error("Open: ", str);
		exit(-1);
	}
	return (fd);
}
