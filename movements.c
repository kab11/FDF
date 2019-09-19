/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 21:36:24 by kblack            #+#    #+#             */
/*   Updated: 2019/09/02 21:36:30 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
            j++;
        }
        i++;
    }
}

void mtx_vec_multi(float mtx[4][4], t_map *vec)
{
    int i;
    int j;
    float out[4];
    float vector[4];

    i = 0;
    vector[0] = vec->x;
    vector[1] = vec->y;
    vector[2] = vec->z;
    vector[3] = 1;
    while (i < 4)
    {
        j = 0;
        out[i] = 0;
        while (j < 4)
        {
            out[i] += mtx[i][j] * vector[j];
            j++;
        }
        i++;
    }
    vec->x = out[0];
    vec->y = out[1];
    vec->z = out[2];
}

void mtx_copy(float src[4][4], float dst[4][4])
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dst[i][j] = src[i][j];
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

void translate(float mtx[4][4], float tx, float ty, float tz)
{
    float t_mtx[4][4];
    float tmp[4][4];

    identity_mtx(t_mtx); 
    identity_mtx(tmp); 
    t_mtx[0][3] = tx;
    t_mtx[1][3] = ty;
    t_mtx[2][3] = tz;
    mtx_multi(mtx, t_mtx, tmp);
    // mtx_copy(tmp, mtx);
}


void translate_map(t_utl *utl, int changex, int changey)
{
    float translation_matrix[4][4];
	int x;
	int y;

    translate(translation_matrix, changex, changey, 0);
	y = -1;
	while (utl->row > ++y)
    {
        x = -1;
        while (utl->col > ++x)
        {
			// utl->mtx[y][x].x += changex;
			// utl->mtx[y][x].y += changey;
            mtx_vec_multi(translation_matrix, &utl->map[y][x]);
        }
    }
}
