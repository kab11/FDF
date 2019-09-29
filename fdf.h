 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:14:40 by kblack            #+#    #+#             */
/*   Updated: 2019/05/13 04:03:47 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>

# define MIN(a, b) (a > b) a : b
# define MAX(a, b) (a > b) b : a
# define WIDTH 1000
# define HEIGHT 1000

/*
** struct node of linked list
*/

typedef struct	s_map
{
  float x;
  float y;
  float z;
}				t_map;

typedef struct	s_img
{
	void				*image;
	int					*buf;
	int					bpp;
	int					len;
	int					endian;
}				t_img;

typedef struct  s_utl
{
  int height;
  int width;
  int keys[256];
  void *m_ptr;
  void *w_ptr;
  t_map **map;
  int scale;

  t_img *img;
}               t_utl;

void		free_double_ptr(char **ptr);
// void    draw(int x0, int y0, int x1, int y1);
void coordinates(t_map **mtx, t_utl *utl);
void draw_line_to_image(t_map p0, t_map p1, t_utl *utl);
void translate(float mtx[4][4], float tx, float ty, float tz);
void translate_map(t_utl *utl, float changex, float changey);

#endif