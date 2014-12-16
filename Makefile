# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/08 15:08:34 by bbecker           #+#    #+#              #
#    Updated: 2014/12/14 14:01:12 by bbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

F = ./srcs/

I = -I./headers

L = -L /usr/X11/lib -lmlx -lXext -lX11 -L./lib -lft

TOMAKE =	$(F)count.c			\
			$(F)fdf.c			\
			$(F)printtab.c		\
			$(F)writeintab.c	\
			$(F)createelem.c	\
			$(F)get_next_line.c	\
			$(F)readfile.c		\
			$(F)display.c		\
			$(F)displayseg.c	\
			$(F)movenscale.c

TOLIB	=	count.o				\
			fdf.o				\
			printtab.o			\
			writeintab.o		\
			createelem.o		\
			get_next_line.o		\
			readfile.o			\
			display.o			\
			displayseg.o		\
			movenscale.o

all: $(NAME)

$(NAME):
	make -C ./lib/libft
	gcc -c -Wall -Werror -Wextra $(TOMAKE) $(I) $(L)
	gcc -Wall -Werror -Wextra $(I) $(L) -o $(NAME) $(TOLIB)

clean :
	/bin/rm -rf $(TOLIB)

fclean: clean
	/bin/rm -f $(NAME)
	#/bin/rm -f ./lib/libft.a

re: fclean all
