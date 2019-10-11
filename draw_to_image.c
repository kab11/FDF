/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 23:05:39 by kblack            #+#    #+#             */
/*   Updated: 2019/09/22 23:05:51 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_pixel_to_image(t_utl *utl, int x, int y, int color)
{
	int location;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return;
	location = x + (y * WIDTH);
	if (location < WIDTH * HEIGHT)
		utl->img->buf[location] = color;
}

int swap_coordinates(t_map *p0, t_map *p1)
{
	float tmp;

	tmp = 0;
	if (fabs(p1->x - p0->x) > fabs(p1->y - p0->y))
		return (0);
	tmp = p0->y;
	p0->y = p0->x;
	p0->x = tmp;

	tmp = p1->y;
	p1->y = p1->x;
	p1->x = tmp;

	return (1);
}

void draw_line_to_image(t_map p0, t_map p1, t_utl *utl)
{
	float dx;
	float dy;
	float dz;
	float slope;
	float error = -1.0;
	int swap;

	swap = swap_coordinates(&p0, &p1);
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	dz = p1.z - p0.z;
	slope = fabs(dy / dx);
	while ((int)p0.x != (int)p1.x)
	{
		draw_pixel_to_image(utl, swap ? p0.y : p0.x, swap ? p0.x : p0.y, 0xFFFFFF);
		error += slope;
		if ((int)error >= 0)
		{
			p0.y += (p0.y > p1.y) ? -1 : 1;
			error -= 1;
		}
		p0.z += dz / fabs(dx);
		p0.x += (p0.x > p1.x) ? -1 : 1;
	}
	draw_pixel_to_image(utl, swap ? p0.y : p0.x, swap ? p0.x : p0.y, 0xFFFFFF);
}

int is_on_screen(t_map point)
{
	return (point.x > -1 && point.x < WIDTH && point.y > -1 && point.y < HEIGHT);
}

void coordinates(t_map **mtx, t_utl *utl)
{ 
    int x;
    int y;
    
    y = -1;
    while (++y < utl->height)
    {
        x = -1;
        while (++x < utl->width)
        {
			if (x < utl->width - 1)
			{
				if (is_on_screen(mtx[y][x]) || is_on_screen(mtx[y][x + 1]))
					draw_line_to_image(mtx[y][x], mtx[y][x + 1], utl);
			}
			if (y < utl->height - 1)
			{
				if (is_on_screen(mtx[y][x]) || is_on_screen(mtx[y + 1][x]))
					draw_line_to_image(mtx[y][x], mtx[y + 1][x], utl);
			}
        }
    }
}
