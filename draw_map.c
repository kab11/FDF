/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:32:25 by kblack            #+#    #+#             */
/*   Updated: 2019/08/24 15:32:36 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line_rows(int x0, int y0, int x1, int y1, t_utl utl)
{
    int	x;
    int	y;
	int	dx;
    int	dy;
	int	p;
	int	step;

    x = 0;
    y = 0;
	dx = x1 - x0;
	dy = y1 - y0;
    step = dy < 0 ? 1 : -1;
    dy *= step;
    p = 2 * dy - dx;
    y = y0;
    while (x < x0)
    {
        mlx_pixel_put(utl.m_ptr, utl.w_ptr, x, y, 0xFFFFFF);
        if (p > 0)
        {
            y = y + step;
            p = p - 2 * dx;
        }
        p = p + 2 * dy;
        x++;
    }
}

void	plot_line_colums(int x0, int y0, int x1, int y1, t_utl utl)
{
    int	x;
    int	y;
	int	dx;
    int	dy;
	int	p;
	int	step;

    x = 0;
    y = 0;
	dx = x1 - x0;
	dy = y1 - y0;
    step = dx < 0 ? 1 : -1;
    dx *= step;
    p = 2 * dx - dy;
    x = x0;
    while (y < y0)
    {
        mlx_pixel_put(utl.m_ptr, utl.w_ptr, x, y, 0xFFFFFF);
        if (p > 0)
        {
            x = x + step;
            p = p - 2 * dy;
        }
        p = p + 2 * dx;
        y++;
    }
}

void	coordinates(t_map **mtx, t_utl utl)
{
    int	i;
    int	x;
    int	y;
    int	scale;
    
    i = 1;
    y = -1;
    scale = 10;
    while (utl.row > ++y)
    {
        x = -1;
        while (utl.col > ++x)
        {
            printf("y = %d\t x = %d\n", ft_abs(y), ft_abs(x));
            if (x < utl.col)
                plot_line_rows(mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y][x+1].x + scale * x, mtx[y][x+1].y + scale * y, utl);
            if (y < utl.row)
                plot_line_colums(mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y+1][x].x + scale * x, mtx[y+1][x].y + scale * y, utl);
        }
    }
}
