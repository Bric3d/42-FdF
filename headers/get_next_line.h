/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:10:47 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/14 18:19:24 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 42

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int	get_next_line(int const fd, char **line);

typedef struct	s_infos
{
	int		start;
	char	*tmp;
	int		state;
	int		end;
}				t_infos;

#endif
