/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:11:59 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/03 14:25:41 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

int		ft_openfile(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		perror(/*str,*/ "Open");
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
		perror(/*str ,*/"Malloc");
		exit(-1);
	}
	line->nxt = NULL;
	line->line = NULL;
	return (line);
}

void	ft_disp_basemap(t_line *line)
{
	line = line->first;
	ft_putendl("Here is your map :");
	while (line && line->line)
	{
		ft_putendl(line->line);
		line = line->nxt;
	}
}

/*int*/void/****/ ft_convertmap(t_line *line)
{
	int i;

	line = line->first;
	i = ft_count_line(line);
	ft_putchar('\n');
	ft_putnbr(i);
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
	ft_disp_basemap(line);
	ft_convertmap(line);
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
