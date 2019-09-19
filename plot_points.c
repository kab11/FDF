/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 21:56:40 by kblack            #+#    #+#             */
/*   Updated: 2019/05/15 21:56:47 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void bresenham(int x0, int y0, int z0, int x1, int y1, int z1, t_utl utl)
{
	int xstep;
	int ystep;
	int zstep;
	int p1;
	int p2;
	int dx;
	int dy;
	int dz;

	// dx = abs(x1 - x0);
	// dy = abs(y1 - y0);
	// dz = abs(z1 - z0);

	dx = x1 - x0;
	dy = y1 - y0;
	dz = z1 - z0;

	xstep = (dx < 0) ? -1 : 1;
	ystep = (dy < 0) ? -1 : 1;
	zstep = (dz < 0) ? -1 : 1;

	dx *= xstep;
	dy *= ystep;
	dz *= zstep;

	printf("x = %d\t y = %d\t z = %d\n", xstep, ystep, zstep);
	if (dx >= dy && dx >= dz)
	{
		p1 = 2 * dy - dx;
		p2 = 2 * dz - dx;
		while (x0 != x1)
		{
			x0 += xstep;
			if (p1 >= 0)
			{
				y0 += ystep;
				p1 -= 2 * dx;
			}
			if (p2 >= 0)
			{
				z1 += zstep;
				p2 -= 2 * dx;
			}
			p1 += 2 * dy;
			p2 += 2 * dz;
			mlx_pixel_put(utl.m_ptr, utl.w_ptr, x0, y0, 0xFFFFFF);
		}
	}
	else if (dy >= dx && dy >= dz)
	{
		p1 = 2 * dx - dy;
		p2 = 2 * dz - dy;
		while (y0 != y1)
		{
			y0 += ystep;
			if (p1 >= 0)
			{
				x0 += xstep;
				p1 -= 2 * dy;
			}
			if (p2 >= 0)
			{
				z1 += zstep;
				p2 -= 2 * dy;
			}
			p1 += 2 * dx;
			p2 += 2 * dz;
			mlx_pixel_put(utl.m_ptr, utl.w_ptr, x0, y0, 0xFFFFFF);
		}
	}
	else
	{
		p1 = 2 * dy - dx;
		p2 = 2 * dz - dx;
		while (z0 != z1)
		{
			z0 += zstep;
			if (p1 >= 0)
			{
				y0 += ystep;
				p1 -= 2 * dz;
			}
			if (p2 >= 0)
			{
				x1 += xstep;
				p2 -= 2 * dz;
			}
			p1 += 2 * dy;
			p2 += 2 * dz;
			mlx_pixel_put(utl.m_ptr, utl.w_ptr, x0, y0, 0xFFFFFF);
		}
	}
}

void coordinates(t_map **mtx, t_utl utl)
{
    int i;
    int x;
    int y;
    int scale = 10;
    
    i = 1;
    y = -1;
    while (utl.row > ++y)
    {
        x = -1;
        while (utl.col > ++x)
        {
            printf("y = %d\t x = %d\n", ft_abs(y), ft_abs(x));
            if (y < x)
            {
                if (mtx[y][x].x > mtx[y][x+1].x)
                    bresenham(mtx[y][x+1].x + scale * x, mtx[y+1][x].y + scale * y, mtx[y][x].z, mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y][x].z, utl);
                else
                    bresenham(mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y][x].z, mtx[y][x+1].x + scale * x, mtx[y+1][x].y + scale * y, mtx[y][x].z, utl);
            }
            else
            {
                if (mtx[y][x].y > mtx[y+1][x].y)
                    bresenham(mtx[y][x+1].x + scale * x, mtx[y+1][x].y + scale * y, mtx[y][x].z, mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y][x].z, utl);
                else
                    bresenham(mtx[y][x].x + scale * x, mtx[y][x].y + scale * y, mtx[y][x].z, mtx[y][x+1].x + scale * x, mtx[y+1][x].y + scale * y, mtx[y][x].z, utl);
            }
        }
    }
}