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

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int deal_key(int key, void *param)
{
	(void)key;
	(void)param;
	ft_putchar('X');
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	int x = 0, y = 0;
	int x1 = 50, y1 = 30;
	int x2 = 100;
	int y2 = 100;
	int dx, dy;
	int p;
	int step = 1;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");

	x = x1;
	y = y1;
	dx = x2 - x;
	dy = y2 - y;
	p = 2 * dy - dx;

	while (dy--)
	{
		printf("p = %d\t x = %d\t y = %d\n", p, x, y);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
		y++;
		if (p < 0)
			p = p + (2 * dx);
		else
		{
			p = p + (2 * dx) - (2 * dy);
			x += step;
		}
	}

	while (x <= x2)
	{
		printf("p = %d\t x = %d\t y = %d\n", p, x, y);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
		x++;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - (2 * dx);
			y++;
		}
	}
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
