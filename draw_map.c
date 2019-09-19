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

void	plot_line_rows(float x0, float y0, float x1, float y1, t_utl *utl)
{
	float	dx;
    float	dy;
	float	p;
	float	step;

	dx = x1 - x0;
	dy = y1 - y0;
    step = dy < 0 ? 1 : -1;
    dy *= step;
    p = 2 * dy - dx;
    while (x0 != x1)
    {
        mlx_pixel_put(utl->m_ptr, utl->w_ptr, x0, y0, 0xFFFFFF);
        if (p > 0)
        {
            y0 = y0 + step;
            p = p - 2 * dx;
        }
        p = p + 2 * dy;
        x0++;
    }
}

void	plot_line_colums(float x0, float y0, float x1, float y1, t_utl *utl)
{
	float	dx;
    float	dy;
    float	p;
	float	step;

	dx = x1 - x0;
	dy = y1 - y0;
    step = dx < 0 ? 1 : -1;
    dx *= step;
    p = 2 * dx - dy;
    while (y0 != y1)
    {
        mlx_pixel_put(utl->m_ptr, utl->w_ptr, x0, y0, 0xFFFFFF);
        if (p > 0)
        {
            x0 = x0 + step;
            p = p - 2 * dy;
        }
        p = p + 2 * dx;
        y0++;
    }
}

void	coordinates(t_map **map, t_utl *utl)
{
    int	x;
    int	y;
    
    y = -1;
    // utl->scale = WIN_HOZ / utl->col;
    while (utl->row > ++y)
    {
        x = -1;
        while (utl->col > ++x)
        {
            if (x + 1 < utl->col)
                plot_line_rows(map[y][x].x, map[y][x].y, map[y][x+1].x, map[y][x+1].y, utl);
            if (y + 1 < utl->row)
                plot_line_colums(map[y][x].x, map[y][x].y, map[y+1][x].x, map[y+1][x].y, utl);
        }
    }
}
