#include "fdf.h"
#include <stdio.h>

int     ft_color(int z)
{
    if (z <= 0)
        return (0x0000ff);
    if (z > 0 && z < 10)
        return (0xF7DF7D);
    if (z > 9 && z < 30)
        return (0x21B84E);
    if (z > 29 && z < 60)
        return (0x21B84E);
    else
        return (0xffffff);
}


void    ft_putpxl(t_env *env, int x, int y, int color)
{
    int size;
    int z;
    int w;

    size = 2;
    z = 0;

    while (z < size)
    {
        w = 0;
        while (w < size)
        {
            mlx_pixel_put(env->init, env->win, x + w + 100, y + z + 100, color);
            w++;
        }
        z++;
    }
}

t_pts   *ft_putxy(int x1, int y1, int x2, int y2)
{
    t_pts *pts;

    pts = (t_pts *)malloc(sizeof(t_pts));
    pts->x1 = x1;
    pts->y1 = y1;
    pts->x2 = x2;
    pts->y2 = y2;
    return (pts);
}

void    ft_bresenham(t_env *env, t_pts *pts, int height)
{
    int        a[5];
    int        e2;

    a[0] = ft_abs(pts->x2 - pts->x1);
    a[1] = pts->x1 < pts->x2 ? 1 : -1;
    a[2] = ft_abs(pts->y2 - pts->y1);
    a[3] = pts->y1 < (pts->y2) ? 1 : -1;
    a[4] = (a[0] > a[2] ? a[0] : -a[2]) / 2;
    while (1)
    {
        ft_putpxl(env, pts->x1, pts->y1, ft_color(height));
        if (pts->x1 == pts->x2 && pts->y1 == pts->y2)
            break ;
        e2 = a[4];
        if (e2 > (-a[0]))
        {
            a[4] -= a[2];
            pts->x1 += a[1];
        }
        if (e2 < a[2])
        {
            a[4] += a[0];
            pts->y1 += a[3];
        }
    }
}

void    ft_initseg(t_env *env, int x, int y, t_lnu *lnu)
{
    int     **tab;
    int     p;
    t_pts   *pts;

    lnu = (void *)lnu;
    p = env->p;
    tab = env->nfo->tab;
    if (x > 0)
    {
        pts = ft_putxy(x * p, y * p - tab[y][x], (x - 1) * p, y * p - tab[y][x - 1]);
        ft_bresenham(env, pts, (tab[y][x] + tab[y][x - 1]) / 2);
    }
    if (y > 0)
    {
        pts = ft_putxy(x * p, y * p - tab[y][x], x * p, (y - 1) * p - tab[y - 1][x]);
        ft_bresenham(env, pts, (tab[y][x] + tab[y - 1][x]) / 2);
    }
}

int     ft_printpixels(t_env *env)
{
    int     **tab;
    t_lnu   *lnu;
    int     x;
    int     y;

    y = 0;
    lnu = env->nfo->lnu;
    tab = env->nfo->tab;
    while (y < env->nfo->linenu)
    {
        x = 0;
        while(x < lnu->llin)
        {
            ft_putnbr(tab[y][x]);
            ft_putchar(' ');
            ft_initseg(env, x, y, lnu);
            x++;
        }
        ft_putchar('\n');
        y++;
        if (lnu->nxt)
            lnu = lnu->nxt;
    }
    return (0);
}

void    ft_displaysize(t_env *env)
{
    int max;

    if (env->nfo->maxcol > env->nfo->linenu)
        max = env->nfo->maxcol;
    else
        max = env->nfo->linenu;
    env->p = 1000 / max;
}

void    ft_replay(t_env *env)
{
    mlx_clear_window(env->init, env->win);
    ft_printpixels(env);
}

int	    ft_key_hook(int keycode, t_env *env)
{
    env = (t_env *)env;
    ft_putnbr(keycode);
    ft_putchar('\n');
    if (keycode == 65307)
        exit (0);
    if (keycode == 45 || keycode == 65453)
    {
        env->p--;
        ft_replay(env);
    }
    if (keycode == 61 || keycode == 65451)
    {
        env->p++;
        ft_replay(env);
    }
    return (0);
}

void    display(t_nfo *nfo)
{
    t_env   *env;

    if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
        ft_error(NULL, "Malloc");
    env->nfo = nfo;
    env->init = mlx_init();
    ft_displaysize(env);
    env->win = mlx_new_window(env->init, 1100, 1100, "FdF");
    mlx_key_hook(env->win, ft_key_hook, env);
    mlx_expose_hook(env->win, ft_printpixels, env);
    mlx_loop(env->init);
}
