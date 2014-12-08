#include "fdf.h"

void    ft_putpxl(void *init, void *win, int x, int y, int color)
{
    mlx_pixel_put(init, win, x, y, color);
    mlx_pixel_put(init, win, x, y + 1, color);
    mlx_pixel_put(init, win, x + 1, y, color);
    mlx_pixel_put(init, win, x + 1, y + 1, color);
}

void    ft_printpixels(t_env *env)
{
    int     **tab;
    t_lnu   *lnu;
    int     x;
    int     y;

    y = 0;
    lnu = env->nfo->lnu;
    tab = env->nfo->tab;
    while (y < lnu->total)
    {
        x = 0;
        while(x < lnu->llin)
        {
            if (tab[y][x] != 0)
                ft_putpxl(env->init, env->win, x * 50, y *50, 0xff0000);
            else
                ft_putpxl(env->init, env->win, x * 50, y * 50, 0xffffff);
            x++;
        }
        y++;
        if (lnu->nxt)
            lnu = lnu->nxt;
    }
}

void    display(t_nfo *nfo)
{
    t_env   *env;

    if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
        ft_error(NULL, "Malloc");
    env->nfo = nfo;
    env->init = mlx_init();
    env->win = mlx_new_window(env->init, nfo->lnu->total * 100, nfo->lnu->llin * 100, "FdF");
    ft_printpixels(env);
    mlx_loop(env->init);
}
