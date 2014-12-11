#include "fdf.h"
#include <stdio.h>

int     ft_color(int z)
{
    if (z < 0)
        return (0x0000ff);
    if (z > 0)
        return (0xff0000);
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
            mlx_pixel_put(env->init, env->win, x + w, y + z, color);
            w++;
        }
        z++;
    }
}

void    ft_putverb(t_pts *pts, t_env *env, int z)
{
    int y;
    int color;

    color = ft_color(z);
    y = pts->y1;
    while (y < pts->y2)
    {
        ft_putpxl(env, pts->x1, y, color);
        y++;
    }
}

void    ft_putverh(t_pts *pts, t_env *env, int z)
{
    int y;
    int color;

    color = ft_color(z);
    y = pts->y1;
    while (y < pts->y2)
    {
        ft_putpxl(env, pts->x1, y, color);
        y--;
    }
}

void    ft_puthord(t_pts *pts, t_env *env, int z)
{
    int x;
    int color;

    color = ft_color(z);
    x = pts->x1;
    while (x < pts->x2)
    {
        ft_putpxl(env, x, pts->y1, color);
        x++;
    }
}

void    ft_puthorg(t_pts *pts, t_env *env, int z)
{
    int x;
    int color;

    color = ft_color(z);
    x = pts->x1;
    while (x < pts->x2)
    {
        ft_putpxl(env, x, pts->y1, color);
        x--;
    }
}

void    ft_putoct1(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->x2 - pts->x1;
    dy = (pts->y2 - pts->y1) * 2;
    dx = 2 * e;
    while (pts->x1 != pts->x2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->x1++;
        if ((e = e - dy) < 0)
        {
            pts->y1++;
            e = e + dx;
        }
    }
}

void    ft_putoct2(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->y2 - pts->y1;
    dx = (pts->x2 - pts->x1) * 2;
    dy = 2 * e;
    while (pts->y1 != pts->y2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->y1++;
        if ((e = e - dx) < 0)
        {
            pts->x1++;
            e = e + dy;
        }
    }
}

void    ft_putoct8(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->x2 - pts->x1;
    dy = (pts->y2 - pts->y1) * 2;
    dx = 2 * e;
    while (pts->x1 != pts->x2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->x1++;
        if ((e = e - dy) < 0)
        {
            pts->y1--;
            e = e + dx;
        }
    }
}

void    ft_putoct7(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->y2 - pts->y1;
    dx = (pts->x2 - pts->x1) * 2;
    dy = 2 * e;
    while (pts->y1 != pts->y2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->y1--;
        if ((e = e - dx) < 0)
        {
            pts->x1++;
            e = e + dy;
        }
    }
}

void    ft_putoct4(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->x2 - pts->x1;
    dy = (pts->y2 - pts->y1) * 2;
    dx = 2 * e;
    while (pts->x1 != pts->x2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->x1--;
        if ((e = e + dy) < 0)
        {
            pts->y1++;
            e = e + dx;
        }
    }
}

void    ft_putoct3(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->y2 - pts->y1;
    dx = (pts->x2 - pts->x1) * 2;
    dy = 2 * e;
    while (pts->y1 != pts->y2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->y1++;
        if ((e = e + dx) < 0)
        {
            pts->x1--;
            e = e + dy;
        }
    }
}

void    ft_putoct5(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->x2 - pts->x1;
    dy = (pts->y2 - pts->y1) * 2;
    dx = 2 * e;
    while (pts->x1 != pts->x2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->x1--;
        if ((e = e - dx) < 0)
        {
            pts->x1--;
            e = e + dy;
        }
    }
}

void    ft_putoct6(t_env *env, t_pts *pts, int z)
{
    int e;
    int dx;
    int dy;
    int color;

    color = ft_color(z);
    e = pts->y2 - pts->y1;
    dx = (pts->x2 - pts->x1) * 2;
    dy = 2 * e;
    while (pts->y1 != pts->y2)
    {
        ft_putpxl(env, pts->x1, pts->y1, color);
        pts->y1--;
        if ((e = e + dx) < 0)
        {
            pts->x1--;
            e = e + dy;
        }
    }
}

void    ft_chos478(t_env *env, t_pts *pts, int z)
{
    int dx;
    int dy;

    if ((dx = pts->x2 - pts->x1) >= -(dy = pts->y2 - pts->y1))
        ft_putoct8(env, pts, z);
    else
        ft_putoct7(env, pts, z);
}

void    ft_chos112(t_env *env, t_pts *pts, int z)
{
    int dx;
    int dy;

    if ((dx = pts->x2 - pts->x1) >= (dy = pts->y2 - pts->y1))
        ft_putoct1(env, pts, z);
    else
        ft_putoct2(env, pts, z);
}

void    ft_chos243(t_env *env, t_pts *pts, int z)
{
    int dx;
    int dy;

    if (-(dx = pts->x2 - pts->x1) >= (dy = pts->y2 - pts->y1))
        ft_putoct4(env, pts, z);
    else
        ft_putoct3(env, pts, z);
}

void    ft_chos356(t_env *env, t_pts *pts, int z)
{
    int dx;
    int dy;

    if ((dx = pts->x2 - pts->x1) <= (dy = pts->y2 - pts->y1))
        ft_putoct5(env, pts, z);
    else
        ft_putoct6(env, pts, z);
}

void    ft_traceseg(t_env *env, t_pts *pts, int z)
{0
    int dx;
    int dy;

    if ((dx = pts->x2 - pts->x1) != 0)
    {
        if (dx > 0)
        {
            if ((dy = pts->y2 - pts->y1) != 0)
            {
                if (dy > 0)
                    ft_chos112(env, pts, z);
                else if (dy < 0 && dx > 0)
                    ft_chos478(env, pts, z);
            }
            else if (dy == 0 && dx > 0)
                ft_puthord(pts, env, z);
        }
        else if (dx < 0)
        {
            if ((dy = pts->y2 - pts->y1) != 0)
            {
                if (dy > 0)
                    ft_chos243(env, pts, z);
                else if (dy < 0 && dx <0)
                    ft_chos356(env, pts, z);
            }
            else if (dy == 0 && dx < 0)
                ft_puthorg(pts, env, z);
        }
    }
    else if (dx == 0)
    {
        if ((dy = pts->y2 - pts->y1) != 0)
        {
            if (dy > 0)
                ft_putverb(pts, env, z);
            else if (dy < 0)
                ft_putverh(pts, env, z);
        }
    }
    free(pts);
}

void    ft_print_vert(int x0, int y0, int x1, int y1, t_env *env, int color)
{
    (void)y1;
    while (x0 < x1)
        ft_putpxl(env, x0++, y0, color);
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

void    ft_initseg(t_env *env, int x, int y, t_lnu *lnu)
{
    int     **tab;
    int     m;
    int     p;
    t_pts   *pts;

    p = 25;
    m = 100;
    tab = env->nfo->tab;
    ft_putendl("Hey1");
    if (x > 0)
    {
        pts = ft_putxy(x * p + m, y * p + m - tab[y][x], (x - 1) * p + m, y * p + m - tab[y][x - 1]);
        ft_traceseg(env, pts, (tab[y][x] + tab[y][x - 1]) / 2);
    }
    ft_putendl("Hey2");
    if (y > 0)
    {
        pts = ft_putxy(x * p + m, y * p + m - tab[y][x], x * p + m, (y - 1) * p + m - tab[y - 1][x]);
        ft_traceseg(env, pts, (tab[y][x] + tab[y - 1][x]) / 2);
    }
    ft_putendl("Hey3");
    if (x + 1 < lnu->llin)
    {
        pts = ft_putxy(x * p + m, y * p + m - tab[y][x], (x + 1) * p + m - tab[y][x + 1], y * p + m);
        ft_traceseg(env, pts, (tab[y][x] + tab[y][x + 1]) / 2);
    }
    ft_putendl("Hey4");
    if (y + 1 < env->nfo->linenu)
    {
        pts = ft_putxy(x * p + m, y * p + m - tab[y][x], x * p + m, (y + 1) * p + m - tab[y + 1][x]);
        ft_traceseg(env, pts, (tab[y][x] + tab[y + 1][x]) / 2);
    }
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
    while (y < env->nfo->linenu)
    {
        x = 0;
        while(x < lnu->llin)
        {
            ft_putnbr(tab[y][x]);
            ft_putchar(' ');
            ft_initseg(env, x, y, lnu);
            if (tab[y][x] != 0)
                ft_putpxl(env, x * 25 + 100, y * 25 + 100 - tab[y][x], 0xff0000);
            else
            {
                ft_putpxl(env, x * 25 + 100, y * 25 + 100, 0xffffff);
                ft_putchar(' ');
            }
            x++;
        }
        ft_putchar('\n');
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
    env->win = mlx_new_window(env->init, 1000, 1000, "FdF");
    ft_printpixels(env);
    mlx_loop(env->init);
}
