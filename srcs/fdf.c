/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:09:03 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/16 17:23:15 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	ft_error(char *str, char *str2)
{
	ft_putstr_fd("FdF: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	perror(str2);
	exit(-1);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_nfo	*nfo;

	if (argc > 1)
	{
		fd = ft_openfile(argv[1]);
		nfo = ft_read_file(fd);
		display(nfo);
	}
	return (0);
}

void	ft_exit(t_env *env)
{
	t_lnu	*lnu;
	t_lnu	*tmp;
	int		i;

	i = 0;
	lnu = env->nfo->lnu->fst;
	while (lnu)
	{
		tmp = lnu->nxt;
		free(lnu);
		lnu = tmp;
	}
	while (i < env->nfo->linenu)
		free(env->nfo->tab[i++]);
	free(env->nfo->tab);
	free(env->nfo);
	free(env->win);
	free(env->init);
	free(env);
	exit (0);
}
