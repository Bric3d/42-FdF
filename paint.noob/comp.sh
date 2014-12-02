clear
cc -Wall -Werror -Wextra fdf.c -I headers -L /usr/X11/lib -lmlx -lXext -lX11 -L./lib -lft -o ./fdf
