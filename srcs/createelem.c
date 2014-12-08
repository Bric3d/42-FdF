/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createelem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:13:06 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/08 14:26:49 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*ft_create_elem(void)
{
	t_line	*line;

	line = NULL;
	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
	{
		ft_error(NULL, "Malloc");
		exit(-1);
	}
	line->nxt = NULL;
	line->line = NULL;
	return (line);
}

t_lnu	*ft_create_lnu(void)
{
	t_lnu	*new;

	new = (t_lnu *)malloc(sizeof(t_lnu));
	new->nxt = NULL;
	new->fst = NULL;
	new->nu = 0;
	new->llin = 0;
	return (new);
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

void	ft_free_all(t_infos *infos)
{
	free(infos->tmp);
	free(infos);
}

void 	freeline(t_line *line)
{
	t_line *linetmp;

	while (line)
	{
		linetmp = NULL;
		if (line->nxt)
			linetmp = line->nxt;
		if (line)
		{
			line->first = NULL;
			line->nxt = NULL;
			free(line->line);
			free(line);
		}
		line = linetmp;
	}
}
