/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:31:08 by kblack            #+#    #+#             */
/*   Updated: 2019/09/24 21:31:12 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allowed functions:	open		read		write		close
**						malloc		free		perror		strerror
**						exit		*all math.h functions
*/

#include "fdf.h"

void mtx_vec_multi(float mtx[4][4], t_map *vec)
{
	float	x;
	float	y;
	float	z;

	x = vec->x * mtx[0][0] + vec->y * mtx[0][1] + vec->z * mtx[0][2] + mtx[0][3];
	y = vec->x * mtx[1][0] + vec->y * mtx[1][1] + vec->z * mtx[1][2] + mtx[1][3];
	z = vec->x * mtx[2][0] + vec->y * mtx[2][1] + vec->z * mtx[2][2] + mtx[2][3];
	vec->x = x;
	vec->y = y;
	vec->z = z;
}


void mtx_multi(float mtx1[4][4], float mtx2[4][4], float dst[4][4])
{
    int y;
    int x;

    y = -1;
    while (++y < 4)
    {
        x = -1;
        while (++x < 4)
        {
            dst[y][x] = mtx1[y][0] * mtx2[0][x] +
                        mtx1[y][1] * mtx2[1][x] +
                        mtx1[y][2] * mtx2[2][x] +
                        mtx1[y][3] * mtx2[3][x];
        }
    }
}

void clear_mtx(float mtx[4][4])
{
	int y;
	int x;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			mtx[y][x] = 0.0f;
		}
	}
}

void identity_mtx(float mtx[4][4])
{
    clear_mtx(mtx);
    mtx[0][0] = 1.0f;
    mtx[1][1] = 1.0f;
    mtx[2][2] = 1.0f;
    mtx[3][3] = 1.0f;
}

void rotation_x(float dst[4][4], float angle)
{
	float	rotate_mtx[4][4];

	identity_mtx(rotate_mtx);
	rotate_mtx[1][1] = cos(angle);
    rotate_mtx[1][2] = -sin(angle);
    rotate_mtx[2][1] = sin(angle);
    rotate_mtx[2][2] = cos(angle);
	mtx_multi(rotate_mtx, dst, dst);
}

void rotation_y(float dst[4][4], float angle)
{
	float	rotate_mtx[4][4];

	identity_mtx(rotate_mtx);
	rotate_mtx[0][0] = cos(angle);
    rotate_mtx[0][2] = sin(angle);
    rotate_mtx[2][0] = -sin(angle);
    rotate_mtx[2][2] = cos(angle);
	mtx_multi(rotate_mtx, dst, dst);
}

void rotation_z(float dst[4][4], float angle)
{
	float	rotate_mtx[4][4];

	identity_mtx(rotate_mtx);
	rotate_mtx[0][0] = cos(angle);
    rotate_mtx[0][1] = -sin(angle);
    rotate_mtx[1][0] = sin(angle);
    rotate_mtx[1][1] = cos(angle);
	mtx_multi(rotate_mtx, dst, dst);
}

void scale_mtx(float dst[4][4], float scale)
{
	float	scale_mtx[4][4];

	identity_mtx(scale_mtx);
	scale_mtx[0][0] = scale;
	scale_mtx[1][1] = scale;
	scale_mtx[2][2] = scale;
	mtx_multi(scale_mtx, dst, dst);
}

void apply_mtx_to_vectors(t_utl *utl, float mtx[4][4])
{
	int x;
	int y;

	y = -1;
	while (++y < utl->height)
	{
		x = -1;
		while (++x < utl->width)
		{
			mtx_vec_multi(mtx, &utl->map[y][x]);
		}
	}
}

void translate_map(t_utl *utl, float changex, float changey)
{
	int x;
	int y;

	y = -1;
	while (utl->height > ++y)
    {
        x = -1;
        while (utl->width > ++x)
        {
			utl->map[y][x].x += changex;
			utl->map[y][x].y += changey;
        }
    }
}

int key_down(int key, t_utl *utl)
{
	// printf("Key: %d\n", key);
	utl->keys[key] = 1;
	return (0);
}

int key_up(int key, t_utl *utl)
{
	utl->keys[key] = 0;
	return (0);
}

int handle_input(t_utl *utl)
{
	float		mtx[4][4];
	float		angle;

	identity_mtx(mtx);
	angle = 0.05f;
	if (utl->keys[53])
		exit(0);
	if (utl->keys[0] || utl->keys[2])
		rotation_y(mtx, (utl->keys[0] ? -angle : angle));
	if (utl->keys[13] || utl->keys[1])
		rotation_x(mtx, (utl->keys[13] ? angle : -angle));
	if (utl->keys[12] || utl->keys[14])
		rotation_z(mtx, (utl->keys[12] ? angle : -angle));
	/*left arrow*/
	if (utl->keys[123])
		translate_map(utl, -20, 0);
	/*right arrow*/
	if (utl->keys[124])
		translate_map(utl, 20, 0);
	/*down arrow*/
	if (utl->keys[126])
		translate_map(utl, 0, -20);
	/*up arrow*/
	if (utl->keys[125])
		translate_map(utl, 0, 20);
	/*spacebar*/
	if (utl->keys[49])
	{
		float x = WIDTH / 2;
		float y = HEIGHT / 2;
		translate_map(utl, -x, -y);
		// projection_mtx(utl, mtx);
		translate_map(utl, x, y);
	}
	if (utl->keys[69] || utl->keys[78])
	{
		scale_mtx(mtx, (utl->keys[69] ? 1.1f : 0.9f));
	}
	translate_map(utl, -WIDTH / 2, -HEIGHT / 2);
	apply_mtx_to_vectors(utl, mtx);
	translate_map(utl, WIDTH / 2, HEIGHT / 2);
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
	ft_bzero(utl->img->buf, sizeof(int) * WIDTH * HEIGHT);
	handle_input(utl);
	coordinates(utl->map, utl);
	mlx_put_image_to_window(utl->m_ptr, utl->w_ptr, utl->img->image, 0, 0);
	return (0);
}

void read_number_col_row(char *line, const char *filename, t_utl *utl)
{
	int				height;
	int				width;
	int				fd;
	char			**tmp;

	height = 0;
	width = 0;
	tmp = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
        ft_printf("OOPS Something is wrong with the file descriptor\n");
	while (get_next_line(fd, &line))
    {
		tmp = ft_strsplit(line, ' ');
		width = count_columns(tmp);
		height++;
		free_double_ptr(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
    }
	close(fd);
	utl->height = height;
	utl->width = width;
	utl->scale = WIDTH / width;
}

void read_map(char *line, t_utl *utl, t_map **map, int fd)
{
	int				x;
	int				y;
	int				x_offset;
	int				y_offset;
	char			**tmp;

	x_offset = WIDTH / 2 - utl->width / 2;
	y_offset = HEIGHT / 2 - utl->height / 2;
	y = 0;
	while (get_next_line(fd, &line))
	{
		tmp = ft_strsplit(line, ' ');
		map[y] = malloc(utl->width * sizeof(t_map));
		x = -1;
		while (tmp[++x])
		{
			map[y][x].x = x + x_offset;
			map[y][x].y = y + y_offset;
			map[y][x].z = ft_atoi(tmp[x]);
		}
		y++;
		free_double_ptr(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
	}
    close(fd);
}

void				set_hooks(t_utl *utl)
{
	mlx_hook(utl->w_ptr, 2, 0, key_down, utl);
	mlx_hook(utl->w_ptr, 3, 0, key_up, utl);
	mlx_loop_hook(utl->m_ptr, render, utl);
}

void				fdf(const char *filename)
{
	int				fd;
	t_utl			utl;
    char			*line;
	t_map			**map;
	t_img			img;

	fd = 0;
	line = NULL;
	ft_bzero(&map, sizeof(map));
	read_number_col_row(line, filename, &utl);
	map = malloc(utl.height * sizeof(t_map *));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
        ft_printf("OOPS Something is wrong with the file descriptor\n");
	read_map(line, &utl, map, fd);
	utl.map = map;
	utl.m_ptr = mlx_init();
	utl.w_ptr = mlx_new_window(utl.m_ptr, WIDTH, HEIGHT, "FDF 42");

	utl.img = &img;
	utl.img->image = mlx_new_image(utl.m_ptr, WIDTH, HEIGHT);
	utl.img->buf = (int *)mlx_get_data_addr(utl.img->image, &(utl.img->bpp), &(utl.img->len), &(utl.img->endian));

	ft_bzero(utl.keys, sizeof(int) * 256);
	set_hooks(&utl);
	mlx_loop(utl.m_ptr);
}

int					main(int argc, char **argv)
{
    if (argc != 2)
	{
        ft_printf("ERROR incorrect number of arguments\n");
		return (0);
	}
	fdf(argv[1]);
    return (0);
}
