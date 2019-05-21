/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:13:36 by kblack            #+#    #+#             */
/*   Updated: 2019/05/01 21:14:25 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }
//
// int deal_key(int key, void *param)
// {
// 	(void)key;
// 	(void)param;
// 	ft_putchar('X');
// 	return (0);
// }
//
// void print_mtx(int n_row, int n_col, t_coordinates **mtx)
// {
// 	int x = 0;
// 	int y = 0;
//
// 	printf("row = %d\t col = %d\n", n_row, n_col);
// 	while (y < n_row)
// 	{
// 		x = 0;
// 		while (x < n_col)
// 		{
// 			printf("[%d] [%d] [%d]\t", mtx[y][x].x, mtx[y][x].y, mtx[y][x].z);
// 			x++;
// 		}
// 		printf("\n");
// 		y++;
// 	}
// }
//
// void open_window()
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
// 	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFF0000);
// 	mlx_key_hook(win_ptr, deal_key, (void *)0);
// 	mlx_loop(mlx_ptr);
// }
//
// /*
// ** Counts the number of columns in the map
// */
//
// int					count_columns(char **tmp)
// {
// 	int				i;
//
// 	i = 0;
// 	while (tmp[i] != '\0')
// 		i++;
// 	return (i);
// }
//
// /*
// ** Uses GNL to find number of rows and columns; closes the file and opens
// ** again to get the xyz-coordinates and store in an array of t_coordinates
// ** structures
// */
//
// void				read_matrix(const char *filename)
// {
// 	int				x = 0;
// 	int				y = 0;
// 	int				n_row = 0;
// 	int				n_col = 0;
// 	char			**tmp = NULL;
//     int				fd = open(filename, O_RDONLY);
//     char			*line = NULL;
// 	t_coordinates	**mtx;
//
//     if (!fd)
//         printf("OOPS\n");
//     while (get_next_line(fd, &line))
//     {
// 		tmp = ft_strsplit(line, ' ');
// 		n_col = count_columns(tmp);
// 		n_row++;
// 		free_double_ptr(tmp);
// 		free(line);
// 		line = NULL;
// 		tmp = NULL;
//     }
// 	close(fd);
//
// 	line = NULL;
// 	ft_bzero(&mtx, sizeof(mtx));
// 	mtx = malloc(n_row * sizeof(t_coordinates *));
// 	fd = open(filename, O_RDONLY);
// 	while (get_next_line(fd, &line))
// 	{
// 		x = -1;
// 		tmp = ft_strsplit(line, ' ');
// 		mtx[y] = malloc(n_col * sizeof(t_coordinates));
// 		while (tmp[++x])
// 		{
// 			mtx[y][x].x = x;
// 			mtx[y][x].y = y;
// 			mtx[y][x].z = ft_atoi(tmp[x]);
// 		}
// 		y++;
// 		free_double_ptr(tmp);
// 		free(line);
// 		line = NULL;
// 		tmp = NULL;
// 	}
//     close(fd);
// 	print_mtx(n_row, n_col, mtx);
// 	open_window();
// }
//
// int					main(int argc, char **argv)
// {
//     if (argc == 2)
//         read_matrix(argv[1]);
//     else
//         ft_printf("ERROR incorrect number of arguments");
//     return (0);
// }

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
