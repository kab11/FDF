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

/* Allowed functions:	open		read		write		close
**						malloc		free		perror		strerror
**						exit		*all math.h functions
*/

#include "fdf.h"

int deal_key(int key, void *param)
{
	(void)key;
	(void)param;
	ft_putchar('X');
	return (0);
}

void print_mtx(int n_row, int n_col, t_map **mtx)
{
	int x = 0;
	int y = 0;

	printf("row = %d\t col = %d\n", n_row, n_col);
	while (y < n_row)
	{
		x = 0;
		while (x < n_col)
		{
			printf("[%d] [%d] [%d]\t", mtx[y][x].x, mtx[y][x].y, mtx[y][x].z);
			x++;
		}
		printf("\n");
		y++;
	}
}

/*
** Counts the number of columns in the map
** >> Doesn't handle if there are 
*/
/*===========NEED TO FIX: will cound too many col for double digits====*/
int					count_columns(char **tmp)
{
	int				i;

	i = 0;
	while (tmp[i] != '\0')
		i++;
	return (i);
}

/*
** Uses GNL to find number of rows and columns; closes the file and opens
** again to get the xyz-coordinates and store in an array of t_coordinates
** structures
*/

void				read_matrix(const char *filename)
{
	int				x = 0;
	int				y = 0;
	int				n_row = 0;
	int				n_col = 0;
	char			**tmp = NULL;
    int				fd = open(filename, O_RDONLY);
    char			*line = NULL;
	t_map	**mtx;

	t_utl	utl;

    if (fd < 0)
        printf("OOPS Something is wrong with the file descriptor\n");
    while (get_next_line(fd, &line))
    {
		tmp = ft_strsplit(line, ' ');
		n_col = count_columns(tmp);
		n_row++;
		free_double_ptr(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
    }
	close(fd);

	line = NULL;
	ft_bzero(&mtx, sizeof(mtx));
	ft_bzero(&mtx, sizeof(mtx));
	mtx = malloc(n_row * sizeof(t_map *));
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		x = -1;
		tmp = ft_strsplit(line, ' ');
		mtx[y] = malloc(n_col * sizeof(t_map));
		while (tmp[++x])
		{
			mtx[y][x].x = x;
			mtx[y][x].y = y;
			mtx[y][x].z = ft_atoi(tmp[x]);
		}
		y++;
		free_double_ptr(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
	}
    close(fd);
	utl.row = n_row - 1;
	utl.col = n_col - 1;
	utl.m_ptr = mlx_init();
	utl.w_ptr = mlx_new_window(utl.m_ptr, 500, 500, "mlx 42");
	print_mtx(n_row, n_col, mtx);
	coordinates(mtx, utl);
	mlx_key_hook(utl.w_ptr, deal_key, (void *)0);
	mlx_hook();
	//mlx_loop(utl.m_ptr);
	// open_window(mtx);
}

int					main(int argc, char **argv)
{
    if (argc == 2)
        read_matrix(argv[1]);
    else
        ft_printf("ERROR incorrect number of arguments");
    return (0);
}