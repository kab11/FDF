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

void mtx_vec_multi(float mtx1[4][4], t_map *vec)
{
	int i;
	float out[4];
	float vector[4];

    i = 0;
	vector[0] = vec->x;
    vector[1] = vec->y;
    vector[2] = vec->z;
    vector[3] = 1;
    while (i < 4)
    {
		out[i]	= 	mtx1[i][0]*vector[0]+
					mtx1[i][1]*vector[1]+
					mtx1[i][2]*vector[2]+
					mtx1[i][3]*vector[3];
        i++;
    }
	vec->x = out[0];	
	vec->y = out[1];
	vec->z = out[2];	
}


void mtx_multi(float mtx1[4][4], float mtx2[4][4], float dst[4][4])
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dst[i][j] = mtx1[i][0]*mtx2[0][j]+
                        mtx1[i][1]*mtx2[1][j]+
                        mtx1[i][2]*mtx2[2][j]+
                        mtx1[i][3]*mtx2[3][j];
			// printf("[%f]\t", dst[i]);
            j++;
        }
        i++;
    }

}


void identity_mtx(float mtx[4][4])
{
    ft_bzero(mtx, sizeof(float) * 4 * 4);
    mtx[0][0] = 1;
    mtx[1][1] = 1;
    mtx[2][2] = 1;
    mtx[3][3] = 1;
}

void rotation_mtx(float rotate_mtx[4][4])
{
	double angle = 0.1f;

	identity_mtx(rotate_mtx);

	/* rotation x */
	rotate_mtx[1][1] = cos(angle);
    rotate_mtx[1][2] = sin(angle);
    rotate_mtx[2][1] = -sin(angle);
    rotate_mtx[2][2] = cos(angle);

	/* rotation y */
	// rotate_mtx[0][0] = cos(angle);
    // rotate_mtx[2][0] = sin(angle);
    // rotate_mtx[0][2] = -sin(angle);
    // rotate_mtx[2][2] = cos(angle);

	/* rotation z */
	// rotate_mtx[0][0] = cos(angle);
    // rotate_mtx[1][0] = -sin(angle);
    // rotate_mtx[0][1] = sin(angle);
    // rotate_mtx[1][1] = cos(angle);
}

void projection_mtx(t_utl *utl, float changex, float changey, float changez)
{
	int x;
	int y;
	float project_mtx[4][4];
	float rotate_mtx[4][4];
	// float combo_mtx[4][4];

	(void)changex;
	(void)changey;
	(void)changez;
	y = -1;
	identity_mtx(project_mtx);
	rotation_mtx(rotate_mtx);
	printf("before\n");
	while (utl->row > ++y)
	{
		x = -1;
		while (utl->col > ++x)
		{
			// mtx_multi(rotate_mtx, project_mtx, combo_mtx);
			mtx_vec_multi(rotate_mtx, &utl->map[y][x]);
			// utl->map[y][x].x *= utl->map[y][x].x * cos(M_PI / 16.0f) - utl->map[y][x].y * sin(M_PI / 16.0f);
			// utl->map[y][x].y *= utl->map[y][x].y * sin(M_PI / 16.0f) + utl->map[y][x].x * cos(M_PI / 16.0f);
		}
	}
	printf("after\n");
}

void translate_map(t_utl *utl, float changex, float changey)
{
	int x;
	int y;

	y = -1;
	while (utl->row > ++y)
    {
        x = -1;
        while (utl->col > ++x)
        {
			utl->map[y][x].x += changex;
			utl->map[y][x].y += changey;
        }
    }
}

int deal_key(int key, t_utl *utl)
{
	/*left arrow*/
	if (key == 123)
		translate_map(utl, -20, 0);
	/*right arrow*/
	if (key == 124)
		translate_map(utl, 20, 0);
	/*down arrow*/
	if (key == 126)
		translate_map(utl, 0, -20);
	/*up arrow*/
	if (key == 125)
		translate_map(utl, 0, 20);
	if (key == 49)
	{
		float	x = utl->map[utl->row / 2][utl->col/2].x;
		float	y = utl->map[utl->row / 2][utl->col/2].y;
		// printf("col = %d\t row = %d\n", utl->col, utl->row);
		// printf("center = (%f\t%f\t%f)\n", utl->map[utl->row / 2][utl->col/2].x, utl->map[utl->row / 2][utl->col/2].y, utl->map[utl->row / 2][utl->col/2].z);
		translate_map(utl, -x, -y);
		// projection_mtx(utl, 0, 0, 0);
		translate_map(utl, x, y);
		// printf("x = %f\t y = %f\n", x, y);
		// translate_map(utl, ((utl->row * utl->scale) / 2), ((utl->col * utl->scale) / 2));
	}
	return (0);
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

int render(t_utl *utl)
{
	mlx_clear_window(utl->m_ptr, utl->w_ptr);
	coordinates(utl->map, utl);
	return (0);
}

void read_number_col_row(char *line, const char *filename, t_utl *utl)
{
	int				n_row;
	int				n_col;
	int				fd;
	char			**tmp;

	n_row = 0;
	n_col = 0;
	tmp = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
        ft_printf("OOPS Something is wrong with the file descriptor\n");
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
	utl->row = n_row - 1;
	utl->col = n_col - 1;
	utl->scale = WIN_HOZ / utl->col;
}

void read_map(char *line, t_utl *utl, t_map **map, int fd)
{
	int				x;
	int				y;
	char			**tmp;

	x = 0;
	y = 0;
	while (get_next_line(fd, &line))
	{
		x = -1;
		tmp = ft_strsplit(line, ' ');
		map[y] = malloc(utl->col * sizeof(t_map));
		while (tmp[++x])
		{
			map[y][x].x = x * utl->scale;
			map[y][x].y = y * utl->scale;
			map[y][x].z = ft_atoi(tmp[x]) * utl->scale;
		}
		y++;
		free_double_ptr(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
	}
    close(fd);
}

void				read_matrix(const char *filename)
{
	int				fd;
	t_utl			utl;
    char			*line;
	t_map			**map;

	fd = 0;
	line = NULL;
	ft_bzero(&map, sizeof(map));
	read_number_col_row(line, filename, &utl);
	map = malloc(utl.row * sizeof(t_map *));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
        ft_printf("OOPS Something is wrong with the file descriptor\n");
	read_map(line, &utl, map, fd);
	utl.map = map;
	utl.m_ptr = mlx_init();
	utl.w_ptr = mlx_new_window(utl.m_ptr, 1000, 1000, "mlx 42");
	mlx_key_hook(utl.w_ptr, deal_key, &utl);
	mlx_loop_hook(utl.m_ptr, render, &utl);
	mlx_loop(utl.m_ptr);
}

int					main(int argc, char **argv)
{
    if (argc == 2)
        read_matrix(argv[1]);
    else
        ft_printf("ERROR incorrect number of arguments");
    return (0);
}
