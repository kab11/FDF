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

# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <string.h>
# include "mlx.h"
# include <sys/stat.h>
# include <fcntl.h>

# define MAX 5000

/*
** struct node of linked list
*/

typedef struct s_coodinates
{
  int x;    // number of rows
  int y;    // number of columns
  int z;    // height
}       t_coordinates;

void		free_double_ptr(char **ptr);

#endif
