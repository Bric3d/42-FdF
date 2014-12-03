/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 10:18:17 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/13 17:05:57 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	b;
	size_t	c;
	char	*data;
	size_t	d;

	b = strlen (s1);
	c = strlen (s2);
	data = (char *)ft_memalloc(sizeof(char) * (b + c + 1));
	d = 0;
	while (d < b && s1[d])
	{
		data[d] = s1[d];
		d++;
	}
	d = 0;
	while (d < c && s2[d])
	{
		data[d + b] = s2[d];
		d++;
	}
	data[b + c + 1] = '\0';
	free(s1);
	free(s2);
	return (data);
}

void	ft_free_all(t_infos *infos)
{
	free(infos->tmp);
	free(infos);
}

int		ft_write_inline(char **line, t_infos *infos)
{
	unsigned int	i;
	size_t			size;
	char			*tmp;

	tmp = infos->tmp;
	size = 0;
	i = infos->start;
	while (tmp[i] && tmp[i++] != '\n')
		size++;
	*line = ft_strsub(tmp, (unsigned int)infos->start, size);
	if (!*line)
		return (-1);
	infos->start = infos->start + size + 1;
	if (!tmp[i])
		infos->end = 1;
	return (1);
}

int		ft_read_fd(int const fd, t_infos *infos)
{
	int		ret;
	char	*buf;

	buf = (char *)ft_memalloc((BUFF_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (ret < 0)
			return (ret);
		infos->tmp = ft_strjoin2(infos->tmp, buf);
		buf = (char *)ft_memalloc((BUFF_SIZE + 1) * sizeof(char));
		if (!buf || infos->tmp == NULL)
			return (-1);
	}
	infos->state = 1;
	free(buf);
	return (ret);
}

int		get_next_line(int const fd, char **line)
{
	static t_infos	*infos;
	int				ret;

	ret = 0;
	if (!infos)
		infos = ft_memalloc(sizeof(infos));
	if (!infos->start)
		infos->start = 0;
	if (!infos->end)
		infos->end = 0;
	if (infos->end == 1)
	{
		ft_free_all(infos);
		return (0);
	}
	if (BUFF_SIZE < 1)
		return (-1);
	if (infos->tmp == NULL)
		infos->tmp = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	if (infos->state == 0)
		ret = ft_read_fd(fd, infos);
	if (ret >= 0)
		ret = ft_write_inline(line, infos);
	return (ret);
}
